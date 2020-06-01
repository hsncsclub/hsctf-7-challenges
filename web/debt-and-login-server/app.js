const express = require("express")
const bodyParser = require("body-parser")
const ejs = require("ejs");

const app = express()
app.use(bodyParser.urlencoded({extended: true}))
app.use(function(req, res, next) {
    res.header("Access-Control-Allow-Origin", "*");
    res.header("Access-Control-Allow-Headers", "Origin, X-Requested-With, Content-Type, Accept");
    next();
  });
app.set("view engine", "ejs");

const getPay = () => parseInt(Math.random() * 100);

const getCost = () => parseInt(Math.random() * 200);

const getgetgetgetgetgetgetgetgetFlag = () => "flag{y0u_f0uND_m3333333_123123123555554322221}";

const yum = {
    functions: ["getPay", "getCost", "getgetgetgetgetgetgetgetgetFlag"]
};

app.route("/").get(function(req, res) {
    res.render("troll");
});

app.route("/yolo_0000000000001")
.get(function(req, res) {
    res.json(yum);
})
.post(function(req, res) {
    const f = req.body.function;
    console.log(req.body, getCost())
    let func;
    switch(f) {
        case "getPay":
            func = getPay;
            break;
        case "getCost":
            func = getCost;
            break;
        case "getgetgetgetgetgetgetgetgetFlag":
            func = getgetgetgetgetgetgetgetgetFlag;
            break;
        case "getFlag": case "flag": case "help":
            func = () => "nice try but no";
            break;
        default:
            func = () => "could not recognize function";
            break;
    }
    res.json({response: func()});
});

app.route("/very-safe-login")
.get(function(req, res) {
    res.render("login", {retry: false});
})
.post(function(req, res) {
    const username = req.body.username;
    const password = req.body.password;
    if (username === "jiminy_cricket" && password === "mushu500") {
        res.render("flag", {flag: "flag{cl13nt_51de_5uck5_135313531}"});
    } else {
        res.render("login", {retry: true})
    }
});



// app.route("/very-safe-login/submit")
// .get();

app.listen(process.env.PORT || 80);
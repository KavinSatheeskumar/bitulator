const express = require('express');
const path = require('path');
const { execFile } = require('child_process');
const bodyParser = require('body-parser')
const app = express();
const port = 80;

app.use(express.static(path.join(__dirname, './frontend/build')));

app.use(bodyParser.urlencoded({
    extended: false
}));
app.use(bodyParser.json());

app.use(function(req, res, next) {
    res.header('Access-Control-Allow-Origin', '*');
    res.header('Access-Control-Allow-Methods', 'GET, POST, OPTIONS');
    res.header('Access-Control-Allow-Headers', 'Content-Type, Authorization, Content-Length, X-Requested-With');

    //intercepts OPTIONS method
    if ('OPTIONS' === req.method) {
      //respond with 200
      res.sendStatus(200);
    }
    else {
    //move on
      next();
    }
});


app.post('/api', (req, res) => {
    console.log(req.body)
    const child = execFile(path.join(__dirname, './compiler/lexer'), [req.body.input])
    child.stdout.on('data', data => {
        console.log(data.toString())
        res.send(data.toString())
    })
})  

app.listen(port, () => {
    console.log(`Listening on ${port}`)
})

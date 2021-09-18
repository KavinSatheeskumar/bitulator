const express = require('express');
const path = require('path');
const { execFile } = require('child_process');
const app = express();
const port = 80;

app.use(express.static(path.join(__dirname, './frontend/build')));


app.get('/api', (req, res) => {
    const child = execFile(path.join(__dirname, './compiler/test-script'), ['Pavlos'])
    child.stdout.on('data', data => {
        res.send(data)
    })
})  

app.listen(port, () => {
    console.log(`Listening on ${port}`)
})

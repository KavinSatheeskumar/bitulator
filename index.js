const express = require('express');
const app = express();
const port = 80;

app.get('/', (req, res) => {
    res.sendFile('./frontend/bitulator/public/index.html')
})  

app.listen(port, () => {
    console.log(`Listening on ${port}`)
})
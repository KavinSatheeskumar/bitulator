const express = require('express');
const path = require('path');
const app = express();
const port = 80;

app.use(express.static(path.join(__dirname, './frontend/build')));

app.get('/', (req, res) => {
    
})  

app.listen(port, () => {
    console.log(`Listening on ${port}`)
})
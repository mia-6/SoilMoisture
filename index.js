const express = require('express');
const bodyParser = require('body-parser');
const path = require('path');

const app = express();
let soilMoisture = 0;

app.use(bodyParser.urlencoded({ extended: false }));
app.use(express.static(path.join(__dirname, 'public')));  // Serving static files

app.get('/data', (req, res) => {
    res.json({ soilMoisture });
});

app.post('/update', (req, res) => {
    if (req.body && req.body.moisture) {
        console.log("Received data:", req.body);
        soilMoisture = parseInt(req.body.moisture, 10);
        res.send("Updated");
    } else {
        res.status(400).send("No moisture data received");
    }
});


const PORT = 2467;
app.listen(PORT, () => {
    console.log(`Server is running on http://localhost:${PORT}`);
});

const express = require('express');
const cors = require('cors');
const app = express();

// ✅ Enable CORS
app.use(cors());

app.use(express.static('public'));
app.use(express.json());

app.post('/check', (req, res) => {
    const word = req.body.word;

    const { exec } = require('child_process');
    exec(`./trie.exe ${word}`, (err, stdout, stderr) => {
        if (err) {
            console.error("Execution error:", stderr);
            res.status(500).send("❌ Error running trie.exe");
        } else {
            res.send(stdout);
        }
    });
});

app.listen(3000, () => {
    console.log("✅ Server is running at http://localhost:3000");
});

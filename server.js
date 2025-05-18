const express = require('express');
const { exec } = require('child_process');
const path = require('path');

const app = express();
const PORT = 3000;

app.use(express.static('public'));
app.use(express.json());

app.post('/check', (req, res) => {
    const word = req.body.word;

    // ✅ Windows-compatible exec (uses trie.exe)
    exec(`trie.exe ${word}`, (err, stdout, stderr) => {
        if (err) {
            console.error("Execution error:", stderr);
            res.status(500).send("❌ Error running trie.exe");
        } else {
            res.send(stdout);
        }
    });
});

app.listen(PORT, () => {
    console.log(`✅ Server is running at http://localhost:${PORT}`);
});
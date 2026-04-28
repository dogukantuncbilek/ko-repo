const express = require('express');
const fs = require('fs');
const path = require('path');

const app = express();
const PORT = 3000;
const SCRIPTS_DIR = path.join(__dirname, 'scripts');

// GET /scripts — list all scripts
app.get('/scripts', (req, res) => {
    const files = fs.readdirSync(SCRIPTS_DIR)
        .filter(f => f.endsWith('.cs'))
        .map(f => ({
            name: f.replace('.cs', ''),
            size: fs.statSync(path.join(SCRIPTS_DIR, f)).size,
            modified: fs.statSync(path.join(SCRIPTS_DIR, f)).mtime
        }));
    res.json(files);
});

// GET /scripts/:name — get script source
app.get('/scripts/:name', (req, res) => {
    const file = path.join(SCRIPTS_DIR, `${req.params.name}.cs`);
    if (!fs.existsSync(file))
        return res.status(404).json({ error: 'Script not found' });

    res.type('text/plain').send(fs.readFileSync(file, 'utf-8'));
});

app.listen(PORT, () => {
    console.log(`Script server running on http://localhost:${PORT}`);
    console.log(`Scripts dir: ${SCRIPTS_DIR}`);
    console.log(`\nEndpoints:`);
    console.log(`  GET /scripts          — list all`);
    console.log(`  GET /scripts/:name    — get source\n`);
});

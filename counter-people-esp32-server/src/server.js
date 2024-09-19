import express from 'express';
import cors from 'cors';

const app = express();

app.use(express.json());
app.use(cors());

let counterPeopleInRoom = 0;

app.get('/', (_, res) => res.status(200).json({ counter: counterPeopleInRoom }));

app.get('/add', (_, res) => {
    counterPeopleInRoom++;
    return res.status(200).json({ messgae: "counter update" });
});

app.get('/remove', (_, res) => {
    if(counterPeopleInRoom <= 0) counterPeopleInRoom--;
    return res.status(200).json({ messgae: "counter update" });
});

app.get('/counter', (_, res) => res.status(200).json({ counter: counterPeopleInRoom }));

app.get('/reset', (_, res) => {
    counterPeopleInRoom = 0;
    return res.status(200).json({ messgae: "counter reset successfully"});
});

app.listen(process.env.PORT, () => console.log("Server is running on"));

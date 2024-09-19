import express from 'express';
import cors from 'cors';

const app = express();

app.use(express.json());
app.use(cors());

let counterPeopleInRoom = 0;

app.get('/add', (_, res) => {
    counterPeopleInRoom++;
    return res.status(200).send();
});

app.get('/remove', (_, res) => {
    if(counterPeopleInRoom > 0) counterPeopleInRoom--;
    return res.status(200).send();
});

app.get('/count', (_, res) => res.status(200).json({ count: counterPeopleInRoom }));

app.get('/reset', (_, res) => {
    counterPeopleInRoom = 0;
    return res.status(200).send();
});

app.listen(process.env.PORT, () => console.log("Server is running on"));
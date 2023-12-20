import express from 'express';
import { createClient } from 'redis';
import { createRequire } from 'module';

// import binding from './build/Release/binding.node';
const require = createRequire(import.meta.url);
const app = express();
const client = createClient();

const mergeSort = require("./build/Release/sort.node");

const port = 8383;

app.use(express.static('public'));
app.use(express.json({ limit: '100mb' }));

client.on('error', err => console.log('Redis Client Error', err));
client.connect().catch(err => console.log(err));

function gracefulShutdown() {
    console.log('Shutting down gracefully...');
    client.bgSave().then(() => {
        client.disconnect().then(() => {
            console.log('Redis client disconnected.');
            process.exit(0); // Exit the process after the client has disconnected.
        });
    });
}

// Listen for the SIGINT signal (e.g., Ctrl+C in the terminal)
process.on('SIGINT', gracefulShutdown);

// Listen for the SIGTERM signal (sent by, e.g., the `kill` command or system shutdown)
process.on('SIGTERM', gracefulShutdown);

// Optional: Listen to the 'exit' event to handle synchronous cleanup
process.on('exit', (code) => {
    // This event does not support asynchronous code, so it's best for synchronous cleanup.
    console.log(`Process exiting with code: ${code}`);
    // Note: It's not safe to call async functions like client.disconnect() here.
});

//Получение данных по URI из базы данных и отправка пользователю
app.get('/:request', getFunctions);

//Отправка данных в базу данных
app.post('/:request', postFunctions);

async function getFunctions(req, res) {
    //Расшифровка параметров из 'GET' запроса для составления URI
    const request = req.params.request;
    const id = req.query.id;
    const sortStatus = req.query.sortStatus;
    let keyName;
    if(!req.query.keyName){
        keyName = `array`;
    }else{
        keyName = req.query.keyName;
    }
    
    let data;
    switch (request) {
        case 'dbSize':
            data = await client.DBSIZE();
            break;
        case 'arraySize':
            data = await client.LLEN(`${keyName}:${id}:${sortStatus}`);
            break;
        case 'array':
            data = await client.LRANGE(`${keyName}:${id}:${sortStatus}`, 0, -1);
            break;
        case 'allArrays':
            let allArrays = [];
            let allNames = await client.keys(`${keyName}:*:${sortStatus}`);
            let size = allNames.length;
            for (let i = 0; i < size; i++) {
                let temp = {
                    array: await client.LRANGE(allNames[i], 0, -1),
                    arrayName: allNames[i]
                };
                allArrays.push(temp);
            }
            data = allArrays;
            break;
        default:
            console.log("Incorrect request specifier: ", request);
            return;
    }
    if (!data) {
        console.log("No data recieved: ", request);
        return;
    }
    res.status(200).send({ info: data });

}

async function postFunctions(req, res) {
    const parsel = req.body.parsel; 
    const request = req.params.request;
    
    let keyName;
    if(!req.query.keyName){
        keyName = `array`;
    }else{
        keyName = req.query.keyName;
    }
    const id = req.query.id.replace(new RegExp(`${keyName}:|:unsorted|:sorted`, 'g'), '');

    if (!parsel) {
        return res.status(400).send({ status: 'failed' });
    }
    
    let sortedArr = parsel[0];
    let unsortedArr = parsel[1];
    
    switch (request) {
        case 'sort':
            //console.log('====>', parsel, keyName);
            let temp;
            if(keyName !== 'array'){
                temp = parsel[0];
            }
            else{
                temp = parsel;
            }
            sortedArr = mergeSort.sort(temp);
            if(temp.length === sortedArr.length)
                res.status(200).json({ info: sortedArr });
            else
                res.status(400);
            break;
        case 'delete':
            client.DEL(`${keyName}:${id}:unsorted`);
            client.DEL(`${keyName}:${id}:sorted`);
            res.status(200).json({ info: 'deleted' });
            break;
        case 'update':
            client.DEL(`${keyName}:${id}:unsorted`);
            client.DEL(`${keyName}:${id}:sorted`);
            console.log(`${keyName}:${id}:`);
            for (let i = 0; i < unsortedArr.length; i++) {
                client.RPUSH(`${keyName}:${id}:unsorted`, `${unsortedArr[i]}`);
                client.RPUSH(`${keyName}:${id}:sorted`, `${sortedArr[i]}`);
            }
            res.status(200).json({ info: sortedArr });
            break;
        case 'add':
            const names = await client.keys(`${keyName}:*:unsorted`);
            let maxId;
            const cleanNames = names.map(name => name.replace(new RegExp(`${keyName}:|:unsorted`, 'g'), ''));
            maxId = Math.max(...cleanNames);
            if (maxId === -Infinity) {
                maxId = 0;
            }
            for (let i = 0; i < unsortedArr.length; i++) {
                //console.log(`${keyName}:${maxId + 1}:unsorted`, `${unsortedArr[i]}`)
                //console.log(`${keyName}:${maxId + 1}:sorted`, `${sortedArr[i]}`)
                client.RPUSH(`${keyName}:${maxId + 1}:unsorted`, `${unsortedArr[i]}`);
                client.RPUSH(`${keyName}:${maxId + 1}:sorted`, `${sortedArr[i]}`);
            }
            res.status(200).json({ info: sortedArr });
            break;
        case 'save':
            client.bgSave();
            break;
        default:
            console.log("something went wrong: request:", request, "id: ", id, "parsel: ", parsel);
            return;
    }
    //res.status(200).send({status: 'recieved'});
}

app.listen(port, () => console.log(`server launched on port: ${port}`));

export default app

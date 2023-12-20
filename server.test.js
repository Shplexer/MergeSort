import request from 'supertest';
import app from './server.js';

let averageTimes = [];
function generateArray(size) {
    const arrays = [];
    for (let i = 0; i < size; i++) {
        const size = Math.floor(Math.random() * 500) + 1; // random array size between 1 and 50
        const array = Array.from({ length: size }, () => (Math.random() * (10000 - (-10000)) + (-10000)).toFixed(5)); // random array contents between 0 and 99
        arrays.push(array);
    }

    return arrays;
}

describe('POST /add', () => {
    describe("uploaded 100 arrays", () => {
        const testSizes = [100, 1000, 10000];
        testSizes.forEach(size => {
            test(`should handle uploading ${size} arrays`, async () => {
                console.log("starting to delete");
                const arrays = generateArray(size);
                for (let i = 0; i < arrays.length; i++) {
                    //console.log(arrays[i], arrays[i+1]);
                    console.debug("post ", i);
                    const response = await request(app).post(`/add?id=0/add?id=0&keyName=testArray`).send({
                        parsel: [[0], arrays[i]]
                    })

                    expect(response.statusCode).toBe(200);
                }

            }, 100 * size);
        });


    });

})

describe('Get and sort arrays', () => {
    describe('Upload and sort 100 random arrays from the database', () => {
        const testSizes = [100, 1000, 10000];
        let unsortedArrays = [];
        testSizes.forEach(size => {
            test(`should get 100 random arrays from a database of ${size} records`, async () => {
                let temp = await request(app).get(`/allArrays?keyName=testArray&sortStatus=unsorted`);
                let data = temp.body.info;
                for (let i = 0; i < 100; i++) {
                    console.log("get ", i);
                    const index = Math.floor(Math.random() * size);
                    //console.log(data[index].array);
                    unsortedArrays.push(data[index].array);
                    expect(temp.statusCode).toBe(200);
                }
            }, 1000 * size); // Timeout is scaled according to the size of the database
            test(`should sort 100 random arrays from a database of ${size} records`, async () => {
                const sortedArrayTimes = [];
                for (let i = 0; i < 100; i++) {
                    console.log("sort ", i);
                    //console.log(unsortedArrays[i]);
                    let temp = [];
                    unsortedArrays[i].forEach(element => {
                        temp.push(parseFloat(element));
                    })
                    //const index = Math.floor(Math.random() * size);
                    let start = performance.now();
                    let response = await request(app).post(`/sort?keyName=testArray&sortStatus=unsorted&id=0`).send({
                        parsel: [temp]
                    });
                    let end = performance.now();
                    sortedArrayTimes.push(end - start);
                    expect(response.statusCode).toBe(200);
                }
                averageTimes.push(`Среднее время работы с массивом в бд с ${size} записями: ${(sortedArrayTimes.reduce((sum, time) => sum + time, 0) / sortedArrayTimes.length).toFixed(3)} мс`);
                

            }, 1000 * size)
        });
    });
})

describe('Delete arrays', () => {
    describe('delete all arrays from the database', () => {
        const testSizes = [100, 1000, 10000];
        let i = 0;
        let lastSize = 0;
        testSizes.forEach(size => {
            size += lastSize;
            test(`should delete ${size} records`, async () => {
                for (i; i < size; i++) {
                    console.log("del ", i);
                    const response = await request(app).post(`/delete?keyName=testArray&sortStatus=unsorted&id=${i + 1}`).send({
                        parsel: [0]
                    });
                    if (i === testSizes.reduce((sum, value) => sum + value, 0) - 1) {
                        averageTimes.forEach(time => console.log(time));
                    }
                    expect(response.statusCode).toBe(200);
                }
            }, 100 * size); // Timeout is scaled according to the size of the database
            lastSize = size;
        });

    });
})
const baseUrl = "http://localhost:8383";

// Функция для получения информации с сервера
async function getInfo(request, arrId, sortStatus) {
	console.time(`get ${request} array:${arrId}:${sortStatus} func`);
	// Отправляем GET запрос с использованием fetch API
	const response = await fetch(`${baseUrl}/${request}?id=${arrId}&sortStatus=${sortStatus}`, {
		method: 'GET' // Указываем метод запроса
	});
	// Парсим ответ в формате JSON
	const data = await response.json();
	//console.log(data.info);
	console.timeEnd(`get ${request} array:${arrId}:${sortStatus} func`);
	return data.info;
}

// Функция для отправки информации на сервер
async function postInfo(input, request, arrId) {
	// Отправляем POST запрос с использованием fetch API
	const response = await fetch(`${baseUrl}/${request}?id=${arrId}`, {
		method: 'POST', // Указываем метод запроса
		headers: {
			"Content-Type": 'application/json'
		},
		body: JSON.stringify({
			parsel: input
		})
	})
	const data = await response.json();
	console.log(data.info);
	return data.info;
}

function inputModeOn() {
	moveHeaderToTopRight();
	clearInput();
	document.querySelector('#input-interface').style.display = 'block';
	document.querySelector('#output-interface').style.display = 'none';
}
function outputModeON() {
	moveHeaderToTopRight();
	clearOutput();
	document.querySelector('#input-interface').style.display = 'none';
	document.querySelector('#output-interface').style.display = 'block';
	getArraysFromDB(false);
}

function moveHeaderToTopRight() {
	const headerContainer = document.querySelector('#header-container');
	headerContainer.classList.add('top-left');
	const inputControl = document.querySelector('#input-control');
	if (inputControl.classList.contains('top')) {
		inputControl.classList.remove('top');
	}

}

function clearInput() {
	document.querySelector('#error-message').style.display = 'none';
	if (document.querySelector('#float-inputs-container')) {
		document.querySelector('#float-inputs-container').remove();
	}
	if (document.querySelector('#input-window')) {
		document.querySelector('#input-window').innerHTML = '';
	}
	const dataSection = document.createElement('div');
	dataSection.id = 'initial-data';
	document.querySelector('#input-window').appendChild(dataSection);

}
function clearOutput() {
	document.querySelector('#error-message').style.display = 'none';
	if (document.querySelector('#float-inputs-container')) {
		document.querySelector('#float-inputs-container').remove();
	}
}

async function sendDataHandler(request, arrId) {
	//!TODO 
	const inputWindow = document.querySelector('#float-inputs-container');
	console.log("dasdasdda", inputWindow.classList);

	inputWindow.querySelectorAll('input').forEach((input, index, array) => {
		checkFloatInput(input);
		if(index === array.length - 1 && array.length > 1) {
			input.classList.remove('error');
		}
	})
	if (inputWindow.querySelectorAll('.error').length > 0) {
		console.log("err");
		displayError('Ошибка: Введены некорректные данные');
	}
	else {
		const confirmationOverlay = document.getElementById('confirmation-overlay');
		let unsortedArr = [];
		let sortedArr = [];
		try {
			clearError();

			confirmationOverlay.style.display = 'block';
			document.querySelector('#loader-confirmation').style.display = 'block';
			inputWindow.querySelectorAll('input').forEach((input, index, array) => {
				//console.log(input.value);
				if (!isNaN(parseFloat(input.value))) unsortedArr.push(parseFloat(input.value));
			})
			console.log("==>", unsortedArr);
			//recievedData = postInfo(arr, request, arrId);
			//postInfo([0], 'save', arrId);
			sortedArr = await postInfo(unsortedArr, 'sort', 'unsorted');
		}
		catch (err) {
			console.log(err);
		}
		finally {
			const acceptBtn = document.getElementById('save');
			const updateBtn = document.getElementById('update');
			updateBtn.style.display = 'none';
			if (request === `update`) {
				acceptBtn.innerText = 'Добавить новую запись';
				updateBtn.style.display = 'inline-block';
				updateBtn.addEventListener('click', () => {
					confirmationOverlay.style.display = 'none';
					const arrays = [sortedArr, unsortedArr];
					postInfo(arrays, 'update', arrId);
					//postInfo([0], 'save', arrId);
				})
				request = 'add';

			}
			acceptBtn.addEventListener('click', () => {
				confirmationOverlay.style.display = 'none';
				const arrays = [sortedArr, unsortedArr];
				postInfo(arrays, request, arrId);
				//postInfo([0], 'save', arrId);
			})
			const cancelBtn = document.getElementById('cancel');
			cancelBtn.addEventListener('click', () => {
				confirmationOverlay.style.display = 'none';
				//postInfo([0], 'save', arrId);
			})
			document.querySelector('#loader-confirmation').style.display = 'none';

			const table = confirmationOverlay.querySelector('table');
			table.style.display = 'table';
			const tbody = table.querySelector('tbody');
			tbody.innerHTML = '';
			//console.log(unsortedArr.length);
			for (let i = 0; i < unsortedArr.length; i++) {
				const row = tbody.insertRow();

				const unsortedEl = row.insertCell();
				const sortedEl = row.insertCell();

				unsortedEl.innerText = unsortedArr[i];
				sortedEl.innerText = sortedArr[i];
			}
		}
	}
	//console.log(recievedData);
}

/**
 * Инициирует процесс ввода и отображения данных массивов,
 * как отсортированных, так и неотсортированных из базы данных.
 * Создает динамическую таблицу в DOM, перечисляющую все массивы
 * с возможностью индивидуальной обработки каждого массива.
 */
function getArraysFromDB(isEditable) {
	const inputControl = document.querySelector('#input-control');

	if (!inputControl.classList.contains('top')) {
		inputControl.classList.add('top');
	}
	let tableParent;
	if (isEditable) {
		clearInput(); // Очищаем ввод
		tableParent = document.querySelector('#input-window');
	}
	else {
		clearOutput(); // Очищаем вывод
		tableParent = document.querySelector('#output-window');
	}
	let unsorted;
	let sorted;
	let unsortedArrays = []; // Массивы до сортировки
	let sortedArrays = []; // Отсортированные массивы
	let unsortedNames = []; // Имена массивов до сортировки
	let sortedNames = []; // Имена отсортированных массивов

	getArrayList(); // Получаем список массивов асинхронно
	function showSpinner() {
		document.getElementById('loader-input').style.display = 'block';
		document.getElementById('loader-output').style.display = 'block';
	}

	function hideSpinner() {
		document.getElementById('loader-input').style.display = 'none';
		document.getElementById('loader-output').style.display = 'none';
	}

	async function getArrayList() {
		try {
			console.time('table time');
			showSpinner();
			unsorted = await getInfo('allArrays', `0`, `unsorted`); // Получаем все массивы
			sorted = await getInfo('allArrays', `0`, `sorted`); // Получаем отсортированные массивы
			console.log("========", unsorted, sorted);

			for (let i = 0; i < unsorted.length; i++) {
				unsortedArrays.push(unsorted[i].array);
				unsortedNames.push(unsorted[i].arrayName);
				sortedArrays.push(sorted[i].array);
				sortedNames.push(sorted[i].arrayName);
				//console.log(unsortedArrays, unsortedNames, "||", sortedArrays, sortedNames);
			}

		} catch (error) {
			console.log(error);
		}
		finally {
			hideSpinner();
			console.timeEnd('table time');
			const arrayNum = unsortedArrays.length;


			if (tableParent.querySelector('table')) {
				tableParent.querySelector('table').remove();
			}
			const table = document.createElement('table'); // Создаем таблицу
			const thead = table.createTHead(); // Создаем заголовок таблицы
			const tbody = table.createTBody(); // Создаем тело таблицы
			const headerRow = thead.insertRow(); // Создаем строку заголовка

			// Создание заголовков для столбцов "№", "sorted" и "unsorted"
			const idHeader = document.createElement('th');
			idHeader.textContent = '#';
			headerRow.appendChild(idHeader);

			const unsortedHeader = document.createElement('th');
			unsortedHeader.textContent = 'Неотсортированный';
			headerRow.appendChild(unsortedHeader);

			const sortedHeader = document.createElement('th');
			sortedHeader.textContent = 'Отсортированный';
			headerRow.appendChild(sortedHeader);

			const sizeHeader = document.createElement('th');
			sizeHeader.textContent = 'Размер';
			headerRow.appendChild(sizeHeader);

			// Вставляем строки в тело таблицы
			for (let i = 0; i < arrayNum; i++) {

				// Создаем новую строку
				const row = tbody.insertRow();

				// Создаем ячейку для номера
				const idCell = row.insertCell();
				idCell.textContent = i + 1;

				// Создаем ячейку для неотсортированного массива
				const unsortedCell = row.insertCell();
				unsortedCell.textContent = `${unsortedArrays[i][0]}...${unsortedArrays[i][unsortedArrays[i].length - 1]}`;
				unsortedCell.addEventListener('click', () => { displayArray(unsortedArrays[i], isEditable, sortedNames[i]);});
				unsortedCell.style.cursor = 'pointer';
				unsortedCell.className = 'clickable';

				// Создаем ячейку для отсортированного массива
				const sortedCell = row.insertCell();
				console.log(sortedArrays[i]);
				sortedCell.textContent = `${sortedArrays[i][0]}...${sortedArrays[i][sortedArrays[i].length - 1]}`;
				sortedCell.addEventListener('click', () => { displayArray(sortedArrays[i], isEditable); });
				sortedCell.style.cursor = 'pointer';
				sortedCell.className = 'clickable';

				// Создаем ячейку для размера массива
				const sizeCell = row.insertCell();
				sizeCell.textContent = unsortedArrays[i].length;
				if(isEditable){
					const deleteCell = row.insertCell();
					deletePic = document.createElement('img');
					deletePic.src = 'img/delete.png';
					deleteCell.appendChild(deletePic);
					deletePic.style.cursor = 'pointer';
					deletePic.style.width = `50px`;
					deletePic.addEventListener('click', () => { deleteArray(sortedNames[i]); });
				}

			}

			// Добавляем таблицу в документ или конкретный контейнер
			tableParent.appendChild(table);
		}
	}
	function deleteArray(arrayName) {
		postInfo([0],'delete', arrayName);
		setTimeout(() => {
			clearInput();
			getArraysFromDB(false);
		}, 100);
	}
	/**
	 * Отображает массив, создавая текстовые поля для каждого элемента.
	 *
	 * @param {Array} arr - Массив значений для отображения.
	 */
	function displayArray(arr, isEditable, arrayName) {
		// Создаем контейнер для ввода чисел с плавающей точкой
		let inputContainer = createFloatInputsContainer();
		console.log(arrayName);
		if (arrayName) {
			inputContainer.classList.add(`update`);
			inputContainer.classList.add(arrayName);
		}
		console.log(inputContainer, inputContainer.classList);
		// Проходимся по массиву и создаем текстовое поле для каждого элемента
		for (let i = 0; i < arr.length; i++) {
			const input = document.createElement('input');
			input.type = 'text';
			input.value = arr[i];
			inputContainer.appendChild(input);
			if (!isEditable) {
				input.disabled = true;
			}
		}
		manualInput(isEditable, inputContainer);
	}
	/**
	 * Создает контейнер для плавающих полей ввода,
	 * удаляя предыдущий контейнер, если он существует.
	 *
	 * @return {HTMLElement} Новый элемент контейнера.
	 */
	function createFloatInputsContainer() {
		// Если контейнер уже существует, удаляем его
		if (document.querySelector('#float-inputs-container')) {
			document.querySelector('#float-inputs-container').remove();
		}

		// Создаем новый контейнер и задаем ему идентификатор
		const container = document.createElement('div');
		container.id = 'float-inputs-container';

		return container;
	}
}

/**
 * Создает и возвращает новую кнопку с указанным текстом и id.
 *
 * @param {string} id - Уникальный идентификатор кнопки
 * @param {string} text - Текст для отображения на кнопке
 * @return {HTMLElement} Новый элемент кнопки
 */
function createButton(id, text) {
	const btn = document.createElement('button');
	btn.innerText = text;
	btn.id = id;
	return btn;
}
// Функция для отображения сообщения об ошибке
function displayError(message) {
	errorMessageElement = document.querySelector('#error-message');
	errorMessageElement.style.display = 'block';
	errorMessageElement.innerText = message;
}

// Функция для очистки сообщения об ошибке
function clearError() {
	errorMessageElement = document.querySelector('#error-message');
	errorMessageElement.style.display = 'none';
	errorMessageElement.innerText = '';
}
/**
 * Инициализирует пользовательский интерфейс для генерации случайного ввода,
 * настраивает обработчики событий для проверки ввода и действий кнопок,
 * а также управляет динамическим созданием и манипуляцией элементами
 * ввода для размера массива и генерации случайных чисел с плавающей точкой.
 */
function randomInput() {
	const inputControl = document.querySelector('#input-control');
	if (!inputControl.classList.contains('top')) {
		inputControl.classList.add('top');
	}
	clearInput();  // Очищаем все предыдущие введенные данные

	// Получаем элементы DOM для последующего использования
	const errorMessageElement = document.querySelector('#error-message');
	const inputWindow = document.querySelector('#input-window');
	const initialDataElement = document.querySelector('#initial-data');

	// Создаем элементы DOM: поле ввода и кнопки
	const arraySizeInputElement = createArraySizeInput();
	const generateBtn = createButton('generate-button', 'Сгенерировать');
	const cancelBtn = createButton('cancel-button', 'Пересоздать значения');
	const sendBtn = createButton('accept-button', 'Отсортировать');
	sendBtn.addEventListener('click', () => sendDataHandler('add'));

	// Настраиваем элемент initialDataElement с кнопками и полем ввода
	initialDataElement.textContent = 'Введите размер массива: ';
	initialDataElement.appendChild(arraySizeInputElement);
	initialDataElement.append(generateBtn, cancelBtn, sendBtn);

	// Переменная для проверки валидности введенных данных
	let isInputValid = false;

	// Обработчик событий для поля ввода размера массива
	arraySizeInputElement.addEventListener('input', function () {
		handleArraySizeInput(this.value);
	});

	// Обработчик события нажатия на кнопку "Сгенерировать"
	generateBtn.addEventListener('click', function () {
		// Если ввод невалиден, ничего не делаем
		if (!isInputValid) return;
		// Показываем кнопки Принять и Сгенерировать снова
		initialDataElement.querySelector(`#accept-button`).style.display = 'inline-block';
		initialDataElement.querySelector(`#cancel-button`).style.display = 'inline-block';
		setInputWindow(); // Обновляем окно ввода
	});

	// Обработчик события нажатия на кнопку "Сгенерировать снова"
	cancelBtn.addEventListener('click', function () {
		//document.querySelector(`#float-inputs-container`).remove(); // Удаляем контейнер с вводами
		//setInputWindow(); // Обновляем окно ввода
		regenerateFloatInputs();
	})

	/**
	 * Создает и возвращает элемент ввода для размера массива.
	 *
	 * @return {HTMLInputElement} Элемент ввода для указания размера массива.
	 */
	function createArraySizeInput() {
		const inputElement = document.createElement('input');
		inputElement.type = 'text';
		inputElement.placeholder = 'Размер массива';
		inputElement.id = 'array-size-input';
		return inputElement;
	}

	// Функция обработки ввода размера массива
	function handleArraySizeInput(size) {
		if (size <= 0) {
			displayError('Ошибка: размер массива должен быть больше нуля');
			isInputValid = false;
			return;
		}

		if (!checkIntInput(arraySizeInputElement, errorMessageElement)) {
			displayError(errorMessageElement.innerText);
			isInputValid = false;
			return;
		}

		clearError(); // Очищаем сообщение об ошибке
		isInputValid = true;
	}

	/**
	 * Настраивает окно ввода, находит или создает контейнер,
	 * изменяет количество элементов ввода в соответствии с 
	 * желаемым размером и добавляет контейнер в окно ввода.
	 */
	function setInputWindow() {
		// Ищем контейнер для ввода или создаем новый, если он не найден
		let inputContainer = document.querySelector('#float-inputs-container') || createFloatInputsContainer();
		let initialSize = inputContainer.querySelectorAll('input').length;
		let targetSize = parseInt(arraySizeInputElement.value);

		// Адаптируем элементы ввода под новый размер
		setInputElements(inputContainer, initialSize, targetSize);
		inputWindow.appendChild(inputContainer);
	}

	// Функция создания контейнера для ввода чисел с плавающей точкой
	function createFloatInputsContainer() {
		const container = document.createElement('div');
		container.id = 'float-inputs-container';
		return container;
	}

	/**
	 * Настраивает количество элементов ввода в контейнере
	 * согласно указанному целевому размеру. Удаляет существующие
	 * элементы ввода, если целевой размер меньше начального, и
	 * добавляет новые, если целевой размер больше начального.
	 *
	 * @param {Element} container - DOM элемент для изменения
	 * @param {number} initialSize - текущее количество элементов ввода
	 * @param {number} targetSize - желаемое количество элементов ввода
	 * @return {void}
	 */
	function setInputElements(container, initialSize, targetSize) {
		// Удаляем лишние элементы ввода, если новый размер меньше текущего
		while (initialSize > targetSize) {
			const lastInput = container.querySelector('input:last-child'); // Находим последний элемент ввода
			if (lastInput) container.removeChild(lastInput); // Удаляем последний элемент ввода
			initialSize--; // Уменьшаем счетчик текущего размера
		}

		// Добавляем новые элементы ввода, если новый размер больше текущего
		for (let i = initialSize; i < targetSize; i++) {
			container.appendChild(createRandomFloatInput(i)); // Создаем и добавляем новый элемент ввода
		}
	}

	function regenerateFloatInputs() {
		container = document.querySelector('#float-inputs-container');
		container.querySelectorAll('input').forEach((input, index, array) => {
			input.value = createRandomFloatInput(index).value;
		})
	}
	// Функция создания элемента ввода с случайным числом с плавающей точкой
	function createRandomFloatInput(index) {
		const inputBox = document.createElement('input');
		inputBox.type = 'text';
		inputBox.placeholder = `#${index + 1}`;
		// Устанавливаем случайное значение с плавающей точкой
		inputBox.value = (Math.random() * (10000 - (-10000)) + (-10000)).toFixed(5);
		// Добавляем обработчик события на ввод для проверки корректности числа с плавающей точкой
		inputBox.addEventListener('input', function () {
			checkFloatInput(this, errorMessageElement)
		});
		return inputBox;
	}
}
/**
 * Инициализирует интерфейс для ручного ввода данных пользователем.
 * Очищает предыдущие вводы, настраивает ссылки на DOM, создает кнопки
 * и поля ввода, а также добавляет обработчики событий для проверки
 * фокуса и валидации ввода. Позволяет динамически создавать новые поля 
 * ввода и проверяет, что все введенные данные являются числами с 
 * плавающей точкой.
 */
function manualInput(isEditable, inputsToFill) {
	const inputControl = document.querySelector('#input-control');
	if (!inputControl.classList.contains('top')) {
		inputControl.classList.add('top');
	}
	// Очищаем все ранее введенные данные.
	clearInput();
	let inputArea;
	// Получаем ссылки на DOM-элементы, с которыми будем работать.
	if (isEditable) {
		inputArea = document.querySelector('#input-window'); // Область, куда пользователь будет вводить данные.
		const dataSection = document.querySelector('#initial-data'); // Секция с начальными данными.
		// Создаем кнопки "Принять" и "Ввести снова" и добавляем их в секцию данных.
		const sendBtn = createButton('accept-button', 'Отсортировать');
		const cancelBtn = createButton('cancel-button', 'Ввести снова');
		cancelBtn.addEventListener('click', () => {
			manualInput(true);
		})
		sendBtn.style.display = 'inline-block';
		cancelBtn.style.display = 'inline-block';
		dataSection.append(sendBtn, cancelBtn);
		let request = 'add';
		let arrId;
		if (inputsToFill && inputsToFill.classList.length === 2) {
			request = inputsToFill.classList[0];
			arrId = inputsToFill.classList[1];
		}
		sendBtn.addEventListener('click', () => sendDataHandler(request, arrId));
	}
	else {
		inputArea = document.querySelector('#output-window'); // Область, куда пользователь будет вводить данные.
		//dataSection = document.querySelector('#final-data'); // Секция с начальными данными.
	}

	// Создаем контейнер для полей ввода и добавляем его в область ввода.
	const inputDiv = document.createElement('div');
	inputDiv.id = 'float-inputs-container';
	if (isEditable) {
		inputArea.appendChild(inputDiv);
	}
	else {
		inputArea.prepend(inputDiv);
	}

	if (!inputsToFill) {
		// Создаем первое поле ввода, устанавливаем его плейсхолдер и добавляем в контейнер.
		const firstInput = createInput('text');
		firstInput.placeholder = '#1';
		inputDiv.appendChild(firstInput);

		// Навешиваем обработчики событий на первое поле ввода.
		firstInput.addEventListener('focus', inputFocusHandler); // Обработчик фокуса для создания нового поля ввода.
		firstInput.addEventListener('focus', focusValidationHandler); // Обработчик фокуса для валидации всех полей ввода.
		firstInput.addEventListener('input', inputValidationHandler); // Обработчик ввода для валидации данных.
	}
	else {
		console.log(inputsToFill, inputsToFill.querySelectorAll('input'));
		inputsToFill.querySelectorAll('input').forEach((el, index, array) => {
			inputDiv.appendChild(el);
			el.placeholder = `#${index + 1}`;
			el.addEventListener('focus', focusValidationHandler); // Обработчик фокуса для валидации всех полей ввода.
			el.addEventListener('input', inputValidationHandler); // Обработчик ввода для валидации данных.
		});
		console.log(isEditable);
		if(isEditable){
			const lastInput = createInput('text');
			lastInput.placeholder = `#${inputDiv.querySelectorAll('input').length + 1}`;
			lastInput.addEventListener('focus', inputFocusHandler); // Обработчик фокуса для создания нового поля ввода.
			lastInput.addEventListener('focus', focusValidationHandler); // Обработчик фокуса для валидации всех полей ввода.
			lastInput.addEventListener('input', inputValidationHandler); // Обработчик ввода для валидации данных.
			
			inputDiv.appendChild(lastInput);
		}
	}

	// Функция для создания полей ввода.
	function createInput(type) {
		const input = document.createElement('input');
		input.type = type; // Устанавливаем тип поля ввода.
		return input; // Возвращаем созданное поле ввода.
	}

	// Обработчик ввода данных, который валидирует введенные значения.
	function inputValidationHandler(event) {
		const input = event.target; // Получаем элемент, с которым происходит событие.
		console.log(event.target); // Выводим элемент в консоль (для отладки).
		checkFloatInput(input); // Проверяем, что введено вещественное число.
	}

	// Обработчик фокуса, который валидирует все поля ввода, когда одно из них получает фокус.
	function focusValidationHandler(event) {
		const container = event.currentTarget.parentNode;
		const allInputs = container.querySelectorAll('input');
		allInputs.forEach((input, index, array) => {
			if (index !== array.length - 1) {
				checkFloatInput(input);
			}
		});
	}

	// Обработчик события фокуса для добавления нового поля ввода, когда текущее поле получает фокус.
	function inputFocusHandler(event) {
		const container = event.currentTarget.parentNode;
		const newInput = createInput('text');
		newInput.placeholder = `#${container.children.length + 1}`;

		// Если текущее поле ввода не первое, то удаляем обработчик события фокуса, чтобы предотвратить многократное срабатывание.
		if (container.placeholder != '#1') {
			event.currentTarget.removeEventListener('focus', inputFocusHandler);
		}

		// Добавляем новые обработчики событий для фокуса и валидации на новый элемент ввода.
		newInput.addEventListener('focus', inputFocusHandler); 		// Обработчик фокуса, добавляющий новое поле ввода.
		newInput.addEventListener('focus', focusValidationHandler); // Обработчик фокуса, валидирующий все поля ввода.
		newInput.addEventListener('input', inputValidationHandler); // Обработчик ввода, валидирующий введенные данные.

		// Добавляем новое поле ввода в родительский контейнер.
		container.appendChild(newInput);
	}
}

/**
 * Проверяет, является ли ввод элемента целым числом.
 *
 * @param {HTMLElement} element - Элемент ввода для проверки
 * @return {boolean} Возвращает true, если значение - целое число,
 * 					 иначе false
 */
function checkIntInput(element) {
	const value = element.value;
	const intRegex = /^[-+]?[0-9]+$/;
	if (value.match(intRegex)) {
		element.classList.remove('error');
		return true;
	} else {
		element.classList.add('error');
		return false;
	}
}

/**
 * Проверяет, является ли значение элемента вещественным числом.
 *
 * @param {HTMLElement} element - Элемент ввода для проверки.
 * @return {boolean} Возвращает true, если значение является вещественным числом,
 *                   иначе false.
 */
function checkFloatInput(element) {
	const value = element.value;
	const floatRegex = /^[-+]?[0-9]*\.?[0-9]+$/;
	if (value.match(floatRegex)) {
		element.classList.remove('error');
		console.log('true');
		return true;
	} else {
		element.classList.add('error');
		console.log('false');
		return false;
	}
}

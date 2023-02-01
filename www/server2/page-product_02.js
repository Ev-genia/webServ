// "use strict";

// function reverseWords(str) {
//     return str.split("").reverse().join("")
// }

// function process(str)
function process()
{
	// alert("Вы нажали на кнопку");
	// id_item__form.addEventListener('submit', (event)=>{
	// 	event.preventDefault()
	// 	console.log(str)
	// })

	// const formElement = document.getElementById('form'); // извлекаем элемент формы
	// formElement.addEventListener('submit', (e) => 
	// {
	// 	e.preventDefault();
	// 	const formData = new FormData(formElement); // создаём объект FormData, передаём в него элемент формы
	//   // теперь можно извлечь данные
	// 	const name = formData.get('name'); // 'John'
	// 	console.log(name);
	// 	console.log('ok');
	// });

	const form = document.getElementById('form');
    
    form.addEventListener('submit', (e) => {
      e.preventDefault();
      
      const formData = new FormData(form);
      const name = formData.get('nameValue');
      
      console.log(name);
    })



	// console.log(str);
	// console.log(name);
	return;

    var xhr = new XMLHttpRequest();
    xhr.open("POST", "/visitor/detect/1", true);
    xhr.setRequestHeader('Content-Type', 'application/json');
    xhr.send(JSON.stringify({
        value: str
    }));

    xhr.onreadystatechange = function() {
        if (xhr.readyState == XMLHttpRequest.DONE) {
            var jsonResponse = JSON.parse(xhr.responseText)
            console.log(jsonResponse)
            // распарсить ответ от сервера `jsonResponse`
            // window.location.replace(jsonResponse.redirectRoute)
        }
    }
}

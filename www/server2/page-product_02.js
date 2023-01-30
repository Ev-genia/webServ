// "use strict";

// function reverseWords(str) {
//     return str.split("").reverse().join("")
// }

function process(str)
{
	// alert("Вы нажали на кнопку");
	console.log(str);
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

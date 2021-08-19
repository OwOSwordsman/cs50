function checkQ1(event) {
    let button = event.target
    if (button.value == 'Nile River') {
        button.style.backgroundColor = 'lime';
        document.getElementById('q1Result').innerHTML = 'CORRECT!';
    } else {
        button.style.backgroundColor = 'red';
        document.getElementById('q1Result').innerHTML = 'INCORRECT...';
    }
    button.disabled = true;
}

function checkQ2() {
    let input = document.getElementById('q2Input');
    if (input.value == 'Alexander Fleming') {
        document.getElementById('q2Result').innerHTML = 'CORRECT!';
        input.style.backgroundColor = 'lime';
    } else {
        document.getElementById('q2Result').innerHTML = 'INCORRECT...';
        input.style.backgroundColor = 'red';
    }
}

const commandInput = document.getElementById('commandInput');
const runButton = document.getElementById('runButton');
const outputArea = document.getElementById('outputArea');

runButton.addEventListener('click', () => {
    const command = commandInput.value;
    
    // Make an AJAX request to a Flask route for command execution
    fetch('/execute_command', {
        method: 'POST',
        headers: {
            'Content-Type': 'application/x-www-form-urlencoded',
        },
        body: `command=${encodeURIComponent(command)}`,
    })
    .then(response => response.json())
    .then(data => {
        outputArea.value = data.result;
    })
    .catch(error => {
        outputArea.value = "An error occurred while processing the command.";
    });
});

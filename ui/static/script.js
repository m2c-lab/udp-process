// Example starter JavaScript for disabling form submissions if there are invalid fields
(() => {
  'use strict'

  // Fetch all the forms we want to apply custom Bootstrap validation styles to
  const forms = document.querySelectorAll('.needs-validation');

  // Loop over them and prevent submission
  Array.from(forms).forEach(form => {
    form.addEventListener('submit', event => {
      var custom_valid = true;
      if (form.getAttribute('id') == 'main_form') {
        custom_valid = validateEncoderParallelism();
      }
      if (!form.checkValidity() || !custom_valid) {
        event.preventDefault();
        event.stopPropagation();
        form.classList.add('was-validated');
      } else {
        form.classList.remove('was-validated');
      }
    }, false)
  })
})();

// const commandInput = document.getElementById("commandInput");
// const runButton = document.getElementById("runButton");
// const outputArea = document.getElementById("outputArea");

// runButton.addEventListener("click", () => {
//   const command = commandInput.value;

//   // Make an AJAX request to a Flask route for command execution
//   fetch("/execute_command", {
//     method: "POST",
//     headers: {
//       "Content-Type": "application/x-www-form-urlencoded",
//     },
//     body: `command=${encodeURIComponent(command)}`,
//   })
//     .then((response) => response.json())
//     .then((data) => {
//       outputArea.value = data.result;
//     })
//     .catch((error) => {
//       outputArea.value = "An error occurred while processing the command.";
//     });
// });

$(document).ready(function () {
  $("#receive-udp-button").click(function () {
    const form = $(this).closest("form")[0]; // Get the parent form element
    if (!form.checkValidity()) {
      form.classList.add("was-validated");
      return;
    }
    $("#run-loading-spinner").removeClass("visually-hidden");
    $.ajax({
      type: "POST",
      url: "/receive_udp",
      data: {
        localIP: $("#local-ip").val(),
        localPort: $("#local-port").val(),
        remoteIP: $("#remote-ip").val(),
        remotePort: $("#remote-port").val(),
        timeout: $("#timeout").val(),
      },
      success: function (response) {
        var result = response.result;
        $("#terminal-output").val(result);
      },
      error: function (response) {
        var result = response.responseJSON.result;
        $("#terminal-output").val(result);
      },
      complete: function() {
        $("#run-loading-spinner").addClass("visually-hidden");
      }
    });
  });

  $("#run-self-test-button").click(function () {
    $("#run-loading-spinner").removeClass("visually-hidden");
    $.ajax({
      type: "POST",
      url: "/run_self_test",
      success: function (response) {
        var result = response.result;
        $("#terminal-output").val(result);
      },
      error: function (response) {
        var result = response.responseJSON.result;
        $("#terminal-output").val(result);
      },
      complete: function() {
        $("#run-loading-spinner").addClass("visually-hidden");
      }
    });
  });
});

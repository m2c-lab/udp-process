// Example starter JavaScript for disabling form submissions if there are invalid fields
(() => {
  "use strict";

  // Fetch all the forms we want to apply custom Bootstrap validation styles to
  const forms = document.querySelectorAll(".needs-validation");

  // Loop over them and prevent submission
  Array.from(forms).forEach((form) => {
    form.addEventListener(
      "submit",
      (event) => {
        var custom_valid = true;
        if (form.getAttribute("id") == "main_form") {
          custom_valid = validateEncoderParallelism();
        }
        if (!form.checkValidity() || !custom_valid) {
          event.preventDefault();
          event.stopPropagation();
          form.classList.add("was-validated");
        } else {
          form.classList.remove("was-validated");
        }
      },
      false
    );
  });
})();

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
      complete: function () {
        $("#run-loading-spinner").addClass("visually-hidden");
      },
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
      complete: function () {
        $("#run-loading-spinner").addClass("visually-hidden");
      },
    });
  });

  $("#plot-button").click(function () {
    // Show the loading spinner
    $("#plot-spinner").removeClass("visually-hidden");

    // Get the plot index from the input field
    var plotIndex = $("#plot-index").val();

    // Make the AJAX request
    $.ajax({
      type: "POST",
      url: "/plot",
      data: {
        plotIndex: plotIndex,
      },
      success: function (response) {
        // Handle the successful response here
        // Update the HTML content with CIR data and plots
        $("#cirIQContent").html(response.fig1);
        $("#cirLinearPlot").html(response.fig2);
        $("#cirDbPlot").html(response.fig3);
        $("#errorModal").modal("hide");
      },
      error: function (error) {
        // Handle the error response here
        console.error("Error loading CIR data and plots:", error);
        $("#errorModal .modal-body").html("An error occurred: " + error.responseJSON.error);
        $("#errorModal").modal("show");
      },
      complete: function () {
        // Hide the loading spinner when the request is complete
        $("#plot-spinner").addClass("visually-hidden");
      },
    });
  });

  $("#use-default-ip-cfg-button").click(function () {
    $("#local-ip").val("192.168.1.199");
    $("#local-port").val("1234");
    $("#remote-ip").val("192.168.1.128");
    $("#remote-port").val("1234");
  });

  $("#use-self-ip-cfg-button").click(function () {
    $("#local-ip").val("127.0.0.1");
    $("#local-port").val("1234");
    $("#remote-ip").val("127.0.0.1");
    $("#remote-port").val("1234");
  });
});

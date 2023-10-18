window.onload = function() {
    function fetchData() {
        fetch("/data")
        .then(response => response.json())
        .then(data => {
            const moistureLevel = document.getElementById("moisture-level");
            const plantStatus = document.getElementById("plant-status");
            const plantImage = document.getElementById("plant-image");

            if (data.soilMoisture == 4095) {  // If the soil is dry
                moistureLevel.textContent = "Soil Status: Dry";
                plantStatus.textContent = "Plant Status: Needs Watering";
                plantImage.src = "images/dry.png";
            } else {
                moistureLevel.textContent = "Soil Status: Wet";
                plantStatus.textContent = "Plant Status: Well Watered";
                plantImage.src = "images/healthy.png";
            }
        });
    }

    fetchData();  // Call the function once when the page loads
    setInterval(fetchData, 5000);  // Then fetch data every 5 seconds
};

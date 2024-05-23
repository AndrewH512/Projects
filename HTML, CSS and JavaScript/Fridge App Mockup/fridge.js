let isDisplayOn = false;

  function updateClock() {
    const now = new Date();
    const hours = now.getHours() % 12 || 12; 
    const minutes = now.getMinutes().toString().padStart(2, '0');
    const period = now.getHours() < 12 ? 'AM' : 'PM';
    document.getElementById('clock').innerText = `${hours}:${minutes} ${period}`;
  }
  
  let isTVOn = false;
  let isBrowserOn = false;
  let isFridgeOn = false;

  function toggleTV() {
    isTVOn = !isTVOn;
    const tvElement = document.getElementById('tv');
	const tvButton = document.getElementById('tvButton');

    if (isTVOn) {
      tvElement.style.display = 'flex';
	  tvButton.innerText = 'Close Tv';
    } else {
      tvElement.style.display = 'none';
	  tvButton.innerText = 'Start Tv';
    }
  }

  function toggleBrowser() {
    isBrowserOn = !isBrowserOn;
    const browserElement = document.getElementById('browser');
	

    if (isBrowserOn) {
      browserElement.style.display = 'flex';
	  browserButton.innerText = 'Close Browser';
    } else {
      browserElement.style.display = 'none';
	  browserButton.innerText = 'Open Browser';
    }
  }
  
  function toggleFridge() {
    isFridgeOn = !isFridgeOn;
    const fridgeElement = document.getElementById('fridge');
	const fridgeButton = document.getElementById('fridgeButton');

    if (isFridgeOn) {
      fridgeElement.style.display = 'flex';
	  fridgeButton.innerText = 'Close Fridge';
    } else {
      fridgeElement.style.display = 'none';
	  fridgeButton.innerText = 'Open Fridge';
    }
  }
  

  function toggleDisplay() {
    isDisplayOn = !isDisplayOn;
    const tvButton = document.getElementById('tvButton');
    const browserButton = document.getElementById('browserButton');
    const fridgeButton = document.getElementById('fridgeButton');

    if (isDisplayOn) {
      
	  onOffButton.innerText = 'Turn Off';
      tvButton.style.display = 'inline-block';
      browserButton.style.display = 'inline-block';
      fridgeButton.style.display = 'inline-block';
	  toggleTV(); 
      toggleBrowser(); 
      toggleFridge();

      document.querySelectorAll('.display-element').forEach(element => {
        element.style.display = 'block';
      });

      document.getElementById('temperatureValue').innerText = '25°C';
      document.getElementById('insideFridgeValue').innerText = 'Organized';
	  
    } else {
      onOffButton.innerText = 'Turn On';
      tvButton.style.display = 'none';
      browserButton.style.display = 'none';
      fridgeButton.style.display = 'none';
      
      clearDisplay();
    }
  }
  
  function clearDisplay() {
    document.querySelectorAll('.display-element').forEach(element => {
    element.style.display = 'none';
    });
  }

  setInterval(updateClock, 1000);
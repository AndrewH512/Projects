function redirectTo(page) {
      window.location.href = page;
    }

let htmlString = "<p> Fetching file: andrewh512.github.io/SD330/parking.json";
htmlString += "<br> Loading into: 'data' multi-dimensional object (array) ";

async function fetchData() {
	const response = await fetch("https://andrewh512.github.io/SD330/parking.json");
	const data = await response.json();

	for (let i = 0; i < data['parking_lots'].length; i++) {
		let lot = data['parking_lots'][i];
				
		htmlString += "<hr><p>Lot: " + "<a href='space.html?lot=" + encodeURIComponent(lot['name']) + "'>" + lot['name'] + "</a> ";
		htmlString += "<p>Total spaces = " + lot['total_spaces'] + " </p>";
		htmlString += "<p>Comments: " + lot['comments'] + " </p>";
		htmlString += "<p>Map: <br> <img src=" + lot['map_filename'] + " alt=" + lot['map_filename'] + ">";
		}
		document.getElementById('parkingLots').innerHTML = htmlString;
		}

	fetchData();

// Function to retrieve query parameter value by name
function getQueryParam(name) {
        const urlParams = new URLSearchParams(window.location.search);
        return urlParams.get(name);
    }

// Retrieve the lot name from the query parameter
const lotName = getQueryParam('lot');
// Fetch parking lot data and display details for the selected lot
async function fetchParkingLotDetails() {
const response = await fetch("https://andrewh512.github.io/SD330/parking.json");
const data = await response.json();
// Find the selected parking lot
const selectedLot = data.parking_lots.find(lot => lot.name === lotName);
if (selectedLot) {
	// Display parking lot details
    const parkingLotDetails = document.getElementById('parkingLotDetails');
    parkingLotDetails.innerHTML = `
        <h2>${selectedLot.name}</h2>
        <p>Total spaces: ${selectedLot.total_spaces}</p>
        <h3>Spaces In This Lot</h3>
		<hr></hr>
        <ul>
            ${selectedLot.spaces.map(space => `
                <p>Space Number: ${space.space_id}, <br> Type: ${space.type}, <br> Status: ${space.status}</p> <hr></hr>
                 `).join('')}
        </ul>
        <p>Map: <br> <img src="${selectedLot.map_filename}" alt="${selectedLot.map_filename}"></p>
        `;
} else {
    // Handle case where lot name is not found
    const parkingLotDetails = document.getElementById('parkingLotDetails');
     parkingLotDetails.innerHTML = '<p>Lot not found.</p>';
       }
}

fetchParkingLotDetails();
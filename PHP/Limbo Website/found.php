<!--
By Andrew Hennessy and Andrew Hatch
-->
<!DOCTYPE html>
<?php
# Includes the header links
require( 'includes/header.php');
echo'<h1>Report a Found Item !</h1>';
echo'<h4>If you found something, youre in luck: this is the place to report it.</h4>';
echo'<h4>Enter A Found Item Below</h4>';

# Connect to MySQL server and the database
require( '../connect_db.php' ) ;

# Includes these helper functions
require( 'includes/limbo_help.php' ) ;

# Initialize limbo info on a POST
if ($_SERVER [ 'REQUEST_METHOD' ] == 'POST' ){
	
	$finder = $_POST['finder'] ;
	
	$itemname = $_POST['itemname'] ;
	
	$description = $_POST['description'] ;
	
	$location_id = $_POST['location_id'] ;
	
	$create_date = $_POST['create_date'] ;

        $room =$_POST['room'];
	
	#Error checking Names before input
	if ( !valid_item_name($itemname) )
		echo '<p style="color:red; font-size:16px;"> This is invalid! </p>' ;
	else if ( !valid_finder($finder) )
		echo '<p style="color:red; font-size:16px;"> This was not a vaild owner name </p>' ;
	else
		insert_found_record($dbc, $finder, $itemname, $description, $location_id, $create_date, $room);
                echo '<p style="color:red; font-size:16px;"> Added Found Item to Limbo! </p>' ;
}


#Closes the connections
mysqli_close($dbc);

?>
<html>
<form action="found.php" method="POST" >
<table>    
<tr><td>Your Name:</td><td><input type = "text" name = "finder" value="<?php if (isset($_POST['finder'])) echo $_POST['finder'];?>"></td></tr>
<tr><td>Item Name:</td><td><input type = "text" name = "itemname" value="<?php if (isset($_POST['item_name'])) echo $_POST['item_name'];?>"></td></tr>
<tr><td>Description of Item:</td><td><input type = "text" name="description" value="<?php if (isset($_POST['description'])) echo $_POST['description'];?>"></td></tr>    
<tr><td>Location Found:</td><td><select name = "location_id" value="<?php if (isset($_POST['location_id'])) echo $_POST['location_id'];?>">
<option value="Hancock Building">Hancock Building</option>
<option value="Marian Hall">Marian Hall</option>
<option value="Byrne House">Byrne House</option>
<option value="Donnelly Hall">Donnelly Hall</option>
<option value="Fontaine Building">Fontaine Building</option>
</select></td></tr>    
<tr><td>Date and Time Found:</td><td><input type="datetime-local" name="create_date" value="<?php if (isset($_POST['create_date'])) echo $_POST['create_date'];?>"></td></tr>
<tr><td>Room Number:</td><td><input type = "text" name = "room" value="<?php if (isset($_POST['room'])) echo $_POST['room'];?>"></td></tr><br>		
<tr><td><input id = "submitbtn" type = "submit" value="Submit"></td></tr>
</table>
</form>

<h4>Click the link below to view all the found items in the system</h4>
<p><a href="found-1.php">Found Items</a></p>
<h4> Do you see your item in limbo? Click the link below! </h4>
<li><a href="update_found.php">Update Found Stuff</a></li>
	
</body>
</html>
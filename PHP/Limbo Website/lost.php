<!--
By Andrew Hennessy and Andrew Hatch
-->
<?php
# Includes the header links
require( 'includes/header.php');
echo'<h1>Report a Lost item!</h1>';
echo'<h4>If you lost something,this is the place to report it. Enter your lost item below!</h4>';

# Connect to MySQL server and the database
require( '../connect_db.php' ) ;

# Includes these helper functions
require( 'includes/limbo_help.php' ) ;


# Initialize limbo info on a GET
if ($_SERVER[ 'REQUEST_METHOD' ] == 'GET')
{
    $itemname = '';

    $description = '';

    $create_date = '';
 
    $location_id = '';

    $owner = '';
  
    $status = '';
  
    $room ='';
	
}

# Initialize limbo info on a POST
if ($_SERVER[ 'REQUEST_METHOD' ] == 'POST') 
{
    $itemname = $_POST['itemname'];

    $description = $_POST['description'];

    $create_date = $_POST['create_date'];
 
    $location_id = $_POST['location_id'];

    $owner = $_POST['owner'];

    $room =$_POST['room'];
 
    #Error Checking
    if ( !valid_item_name($itemname) )
	echo '<p style="color:red; font-size:16px;"> This is invalid! </p>' ;
    else 
	insert_lost_record($dbc, $itemname, $description , $create_date, $location_id, $owner, $room);
        echo '<p style="color:red; font-size:16px;"> Added Lost Item to Limbo! </p>' ;

}


#Closes the connections
mysqli_close ($dbc);

?>
<table>
<form action="lost.php" method="POST" > 
<tr><td>Owner's Name:</td><td><input type = "text" name = "owner" value="<?php if (isset($_POST['owner'])) echo $_POST['finder'];?>"></td></tr>  
<tr><td>Item Name:</td><td><input type = "text" name = "itemname" value="<?php if (isset($_POST['item_name'])) echo $_POST['item_name'];?>"></td></tr>
<tr><td>Description of Item:</td><td><input type = "text" name="description" value="<?php if (isset($_POST['description'])) echo $_POST['description'];?>"></td></tr>   
<tr><td>Location Lost:</td><td><select name = "location_id" value="<?php if (isset($_POST['location_id'])) echo $_POST['location_id'];?>">
<option value="Hancock Building">Hancock Building</option>
<option value="Marian Hall">Marian Hall</option>
<option value="Byrne House">Byrne House</option>
<option value="Donnelly Hall">Donnelly Hall</option>
<option value="Fontaine Building">Fontaine Building</option>
</select></td></tr>
<tr><td>Room Number:</td><td><input type = "text" name = "room" value="<?php if (isset($_POST['room'])) echo $_POST['room'];?>"></td></tr><br>
<tr><td>Date:</td><td><input type="datetime-local" name="create_date" value="<?php if (isset($_POST['create_date'])) echo $_POST['create_date'];?>"></td></tr>		
<tr><td><input id = "submitbtn" type = "submit" value="Submit"></td></tr>
</table>
</form>

<h4>Click the link below to view all the lost items in the system</h4>
<p><a href="Lost-1.php">Lost Items</a></p>

<h4> Do you need to update your item in limbo? Click the link below! </h4>
<p><a href="update_lost.php">Update Lost Stuff</a></p>
</html>


</body>
</html>


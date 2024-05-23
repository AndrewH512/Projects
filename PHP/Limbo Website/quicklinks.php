<!--
By Andrew Hennessy and Andrew Hatch
-->
<?php
# Includes these helper functions
# Includes the header links
require( 'includes/header.php');
echo '<h1>Quick Links</h1>';
echo'<h4>Here you can view all items in the limbo system</h4>';
echo '<p>Click on the ID number to view more infomation on the item!</p>';

# Includes these helper functions
require( 'includes/limbo_help.php' ) ;


# Connect to MySQL server and the database
require( '../connect_db.php' ) ;

# Initialize limbo info on a GET
if ($_SERVER[ 'REQUEST_METHOD' ] == 'GET')
{
    $itemname = '';

    $description = '';

    $create_date = '';
 
    $location_id = '';

    $owner = '';
  
    $status = '';
	
}

# Initialize limbo info on a POST
if ($_SERVER[ 'REQUEST_METHOD' ] == 'POST') 
{
    $itemname = $_POST['itemname'];

    $description = $_POST['description'];

    $create_date = $_POST['create_date'];
 
    $location_id = $_POST['location_id'];

    $owner = $_POST['owner'];
 
    $status = $_POST['status'];
}
else if($_SERVER[ 'REQUEST_METHOD' ] == 'GET') 
{
     if(isset($_GET['id']))
        show_all_record($dbc, $_GET['id']) ;
}

#Shows all the records with links to show more info
show_all_link_records($dbc);

#Closes the connections
mysqli_close($dbc);

?>


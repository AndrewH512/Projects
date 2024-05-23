<!--
By Andrew Hennessy and Andrew Hatch
-->
<!DOCTYPE html>
<?php
# Includes the header links
require( 'includes/header.php');
echo'<h1>Found Items!</h1>';
echo'<h4>Theses are all the current found items in Limbo!.</h4>';
echo'<h4>Need to add a found item to Limbo? Click on Found!</h4>';


# Connect to MySQL server and the database
require( '../connect_db.php' ) ;

# Includes these helper functions
require( 'includes/limbo_help.php' ) ;

#Shows all found items
show_found_records($dbc);

#Closes the Connection
mysqli_close($dbc);
?>
<html>
<h4> Do you see your item in limbo? Click the link below! </h4>
<li><a href="update_found.php">Update Found Stuff</a></li>
</html>
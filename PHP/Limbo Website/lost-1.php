<!--
By Andrew Hennessy and Andrew Hatch
-->
<!DOCTYPE html>
<?php
# Includes the header links
require( 'includes/header.php');
echo'<h1>Other Lost Items!</h1>';
echo'<h4>Theses are all the current Lost items in Limbo!.</h4>';

# Connect to MySQL server and the database
require( '../connect_db.php' ) ;

# Includes these helper functions
require( 'includes/limbo_help.php' ) ;


#Shows all lost records
show_lost_records($dbc);


#Closes the connection
mysqli_close($dbc);
?>
<html>
<h4> Do you need to update your item in limbo? Click the link below! </h4>
<li><a href="update_lost.php">Update Lost Stuff</a></li>

</html>

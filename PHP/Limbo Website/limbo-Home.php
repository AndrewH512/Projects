<!--
By Andrew Hennessy and Andrew Hatch
Alpha 1.0
11/5/2022
-->
<?php
# Includes the header links
require( 'includes/header.php');
echo'<h1>Welcome to Limbo!</h1>';
echo'<h4>If you lost something, your in luck, this is the place to report it!</h4>';


# Connect to MySQL server and the database
require( '../connect_db.php' ) ;

# Includes these helper functions
require( 'includes/limbo_help.php' ) ;


# Show the records of some items
show_some_records($dbc);

# Close the connection
mysqli_close($dbc);
?>


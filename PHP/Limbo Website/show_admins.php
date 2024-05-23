<?php 
# Admin Header
require('includes/header-admins.php');
echo'<h1>Admins in Limbo</h1>';

# Connect to MySQL server and the database
require( '../connect_db.php' ) ;

# This is our helper functions
require( 'includes/limbo_help.php' ) ;
		
# Create a query to get limbo database info for admin page
$query = 'SELECT first_name, last_name, email, reg_date, pass FROM   users ';
		
# Execute the query
$results = mysqli_query( $dbc , $query ) ;
		
show_admin($dbc);
?>
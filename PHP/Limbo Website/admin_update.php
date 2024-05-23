<!DOCTYPE html>
<html>        
<?php

#The Header for admin pages
require( 'includes/header-admins.php' ) ;
echo'<h1>Update An Admin User!</h1>';

# Connect to MySQL server
require( '../connect_db.php' ) ;

#Theses are our helper functions
require( 'includes/limbo_help.php' ) ;

# Shows all admin users
show_admin($dbc);

if ($_SERVER[ 'REQUEST_METHOD' ] == 'POST') 
{
    $oldEmail = $_POST['user'] ;
    $newFirst_name = $_POST['UpdateFirst_name'] ;
    $newLast_name = $_POST['UpdateLast_name'] ;
    $newEmail = $_POST['UpdateEmail'] ;

    $query='UPDATE users SET first_name = "'.$newFirst_name.'", last_name = "'.$newLast_name.'", email = "'.$newEmail.'" WHERE email = "'.$oldEmail.'"' ;

    $results = mysqli_query($dbc,$query) ;
    check_results($results) ;

    echo '<p style="color:red; font-size:16px;"> Admin Information Updated! </p>' ;
    
}

    
# Close the connection
mysqli_close( $dbc ) ;
	
?>  
<form action="admin_update.php" method="POST">
<tr><td>Email</td><td><input type="text" name="user">
</td>
</tr>
<tr><td>New First Name:</td><td><input type="text" name="UpdateFirst_name">
</td>
</tr>
<tr>
<td>New Last Name:</td><td><input type="text" name="UpdateLast_name">
</td>
</tr>

<tr>
<td>New Email:</td><td><input type="text" name="UpdateEmail">
</td>
</tr>
<tr>
<td><input type="submit" id="submitbtn" >
</td>
</tr>
</form>   
</html>
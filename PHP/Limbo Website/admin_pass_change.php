<!DOCTYPE html>
<html>        
<?php

#The Header for admin pages
require( 'includes/header-admins.php' ) ;
echo'<h1>Change An Admin Password!</h1>';

# Connect to MySQL server
require( '../connect_db.php' ) ;

#Theses are our helper functions
require( 'includes/limbo_help.php' ) ;

# Shows all Admins 
show_admin($dbc);

if ($_SERVER[ 'REQUEST_METHOD' ] == 'POST') 
{
    $user = $_POST['user'] ;
    $newPassword = $_POST['password'] ;
        
    $query='UPDATE users SET pass= SHA2("'.$newPassword.'",256) WHERE email = "'.$user.'"' ;

    $results = mysqli_query($dbc,$query) ;
    check_results($results) ;

    echo '<p style="color:red; font-size:16px;"> Admin Password Changed! </p>' ;
}

 
# Close the connection
mysqli_close( $dbc ) ;
	
?>  
<form action="admin_pass_change.php" method="POST">
<tr><td>Admin's Email</td><td><input type="text" name="user"></td></tr>
<tr><td>New Password:</td><td><input type="password" name="password"></td></tr>
<tr><td><input type="submit" id="submitbtn" ></td></tr>
</table>
</form>   
    
</body>
</html>
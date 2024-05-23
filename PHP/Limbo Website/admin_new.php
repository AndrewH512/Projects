<!DOCTYPE html>
<html>        
<?php

#The Header for admin pages
require( 'includes/header-admins.php' ) ;
echo'<h1>Add An Admin User!</h1>';

# Connect to MySQL server
require( '../connect_db.php' ) ;

#Theses are our helper functions
require( 'includes/limbo_help.php' ) ;

#Adds a new admin from the passed in form
if ($_SERVER[ 'REQUEST_METHOD' ] == 'POST') 
{
  $first_name = $_POST['first_name'] ;
  $last_name = $_POST['last_name'] ;
  $email = $_POST['email'] ;
  $pass = $_POST['pass'] ;

  $queryAddAdmin = 'INSERT INTO users(first_name,last_name, email, pass, reg_date) VALUES ( "'.$first_name.'"  , "'.$last_name.'", "'.$email.'" , SHA2("'.$pass.'",256), "2022-11-17 10:11:34") ' ;

  $resultsAddAdmin = mysqli_query($dbc,$queryAddAdmin) ;
  check_results($resultsAddAdmin) ;

  echo'<p>Sucessfully Add A New Admin!</p>';
    
}

# Shows all Admins 
show_admin($dbc);


#Closes the connections
mysqli_close($dbc);

?>  
<!-- Get inputs from the user. -->
<form action="admin_new.php" method="POST">
<tr>
<td>First Name:</td><td><input type="text" name="first_name"></td>
</tr>
<tr>
<td>Last Name:</td><td><input type="text" name="last_name"></td>
</tr>
<tr>
<td>Email:</td><td><input type="text" name="email"></td>
</tr>
<tr>
<td>User Password:</td><td><input type="password" name="pass"></td>
</tr>
<tr>
<td><input type="submit" id="submitbtn" ></td>
</tr>
</form>
</html>
<!--
By Andrew Hennessy and Andrew Hatch
-->
<?php
# Includes the header links
require( 'includes/header.php');
echo'<h1>Admin Login</h1>';
echo'<p>Enter your email and password!</p>';

# Connect to MySQL server and the database
require( '../connect_db.php' ) ;

# Includes these helper functions
require( 'includes/admin_login_tool.php' ) ;


# Initialize user info on a POST
# This valids the email and password
if ($_SERVER[ 'REQUEST_METHOD' ] == 'POST') {

  $email = $_POST['email'] ;
  $pass = $_POST['pass'] ;
  
  $pid = validate($email, $pass);
  
  #Error Message if fails
  if($pid == -1)
    echo '<p style="color:red; font-size:16px;">Login has failed! Try again.</P>' ;

  else 
    load('adminhome.php', $pid);
      
}
?>

<!-- Get inputs. -->
<html>
<form action="adminlogin.php" method="POST">
<table>
<tr>
<td>Email:</td><td><input type="text" name="email"></td>
</tr>
<tr>
<td>Password:</td><td><input type="password" name="pass"></td>
</table>
<p><input type="submit" ></p>
</form>
</html>
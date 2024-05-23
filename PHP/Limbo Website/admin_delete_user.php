<!DOCTYPE html>
<html>        
<?php

#The Header for admin pages
require( 'includes/header-admins.php' ) ;
echo'<h1>Delete An Admin User!</h1>';

# Connect to MySQL server
require( '../connect_db.php' ) ;

#Theses are our helper functions
require( 'includes/limbo_help.php' ) ;


#Deletes an Admin from the passed in form
if ($_SERVER[ 'REQUEST_METHOD' ] == 'POST') {
        
   $emailDelete = $_POST['delAdmin'] ;
        
   $queryDeleteAdmin = 'DELETE FROM users WHERE email = "'.$emailDelete.'"';

   $resultsDeleteAdmin = mysqli_query($dbc,$queryDeleteAdmin) ;
   check_results($resultsDeleteAdmin) ;

   echo '<p style="color:red; font-size:16px;"> Admin Deleted From Limbo! </p>' ;
}

# Shows all Admins 
show_admin($dbc);


#Closes the connections
mysqli_close($dbc);

?>
    
<form action="admin_delete_user.php" method="POST" >
<tr> 
<td>Email:</td>
<td><input type="text" id="delAdmin" name="delAdmin"></td>
<td></td>
<td colspan="2"><input id = "submitbtn" type = "submit" value="Submit"></td>
</tr>
</table>
    
</body>
</html>
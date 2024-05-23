<!--
By Andrew Hennessy and Andrew Hatch
-->
<!DOCTYPE html>
<?php
# Includes the header links
require( 'includes/header-admins.php');
echo'<h1>Admin Site</h1>';
echo'<h4>Edit the Status of Items in Limbo</h4>';

# Connect to MySQL server and the database
require( '../connect_db.php' ) ;

# Includes these helper functions
require( 'includes/limbo_help.php' ) ;




#Changes the Item Status using ID
if ($_SERVER[ 'REQUEST_METHOD' ] == 'POST') 
{
   $Status = $_POST['Status'];
   $StatusID = $_POST['statusID'];
	
   $queryStatus = 'UPDATE stuff SET status = "'.$Status.'" WHERE id = "'.$StatusID.'"';
	
   $resultStatus = mysqli_query($dbc, $queryStatus);
   check_results($resultStatus);

   echo '<p style="color:red; font-size:16px;"> Stuff Updated! </p>' ;
}

#Shows all the records of the items
show_all_records($dbc);

#Closes the connection
mysqli_close($dbc);

?>
<html>
<form action="admin_edit_stuff.php" method="POST" >
<body>
<td>Change the status of a item. Enter the ID: </td>
<td><select name = "statusID" value="<?php if (isset($_POST['statusID'])) echo $_POST['statusID'];?>">
<option value="1">1</option>
<option value="2">2</option>
<option value="3">3</option>
<option value="4">4</option>
<option value="5">5</option>
<option value="6">6</option>
<option value="7">7</option>
<option value="8">8</option>
<option value="9">9</option>
<option value="10">10</option>
</select></td></tr>
<td width="100"><select name = "Status">
<option value="Lost">lost</option>
<option value="Found">found</option>
</select></td>
<td><input id = "submitbtn" type = "submit" value="Submit"></td>
</tr>
</body>
</table>
</form>
 
</html>
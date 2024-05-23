<!--
By Andrew Hennessy and Andrew Hatch
-->
<!DOCTYPE html>
<?php
# Includes the header links
require( 'includes/header.php');
echo'<h1>Did you find one of theses item?</h1>';
echo'<h4>If you have found one of theses lost items, this is the page where you can update their status.</h4>';

# Connect to MySQL server and the database
require( '../connect_db.php' ) ;

# Includes these helper functions
require( 'includes/limbo_help.php' ) ;

#Change Item Status by the passed in Item ID number
if ($_SERVER[ 'REQUEST_METHOD' ] == 'POST') 
{
   $finder = $_POST['finder'] ;  
   $Status = $_POST['Status'];
   $StatusID = $_POST['statusID'];
	
   $queryStatus = 'UPDATE stuff SET status = "'.$Status.'" WHERE id = "'.$StatusID.'"';
	
   $resultStatus = mysqli_query($dbc, $queryStatus);
   check_results($resultStatus);

   echo '<p style="color:red; font-size:16px;"> Updated Lost Item to Found in Limbo! </p>' ;
}

#Shows all lost records
show_lost_records($dbc);

#Closes the connection
mysqli_close($dbc);
?>
<html>
<form action="update_lost.php" method="POST" >
<tr>
<td>Change Item Status ID</td>
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
</select></td></tr>
<td><select name = "Status">
<option value="found">Found</option>
</select></td>
<td><input id = "submitbtn" type = "submit" value="Submit"></td>
</tr>
<tr><td>Finder's Name:</td><td><input type = "text" name = "finder" value="<?php if (isset($_POST['finder'])) echo $_POST['finder'];?>"></td></tr><br>
</table>
</form>
</body>
</html>
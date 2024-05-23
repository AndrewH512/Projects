<!--
By Andrew Hennessy and Andrew Hatch
-->
<!DOCTYPE html>
<?php
# Includes the header links
require( 'includes/header-admins.php');
echo'<h1>Admin Site</h1>';
echo'<h4>Delete Items in Limbo</h4>';

# Connect to MySQL server and the database
require( '../connect_db.php' ) ;

# Includes these helper functions
require( 'includes/limbo_help.php' ) ;

#Deletes item
if(isset($_POST['id'])) 
{
   delete_item_record($dbc, $_POST['id']);
 
   echo '<p style="color:red; font-size:16px;"> Deleted Stuff From Limbo! </p>' ;
}

#Shows all the records of the items
show_all_records($dbc);

#Closes the connection
mysqli_close($dbc);

?>
<!--Get admin user input to delete an item-->
<form action="admin_delete_stuff.php" method="post" class="table-structure w3-cell">
<td>Change Item Status - Select The ID:</td>
<td><select name = "id" value="<?php if (isset($_POST['id'])) echo $_POST['id'];?>">
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
<input type="submit" value="Delete" class="report-btn"/>
</form>
</div>
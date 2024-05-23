# Driver: Andrew Hatch
# Navigator: Andrew Hennessy
# The purpose of this assigment is to create and populate a database for Limbo
# Version 1.0

USE limbo_db;
#Creating users table
DROP TABLE IF EXISTS users;
CREATE TABLE IF NOT EXISTS users
(
  user_id INT NOT NULL AUTO_INCREMENT,
  first_name VARCHAR(40) NOT NULL,
  last_name VARCHAR(40) NOT NULL,
  email VARCHAR(60) NOT NULL,
  pass TEXT NOT NULL,
  reg_date DATETIME NOT NULL,
  PRIMARY KEY(user_id),
  UNIQUE(email)
);
#Inserting "admin" user
INSERT INTO users(user_id,first_name,last_name, pass, email, reg_date)
VALUES ("0001","admin","admin",SHA2('gaze11e',256),"admin@gmail.com","2022-09-27 15:43:12"); 

#Creating locations table
DROP TABLE IF EXISTS locations;
CREATE TABLE IF NOT EXISTS locations
(
  id INT NOT NULL AUTO_INCREMENT,
  create_date DATETIME NOT NULL,
  update_date DATETIME NOT NULL,
  name TEXT NOT NULL,
  PRIMARY KEY(id)
);
#Creating stuff table
DROP TABLE IF EXISTS stuff;
CREATE TABLE IF NOT EXISTS stuff
(
  id INT NOT NULL AUTO_INCREMENT,
  location_id TEXT NOT NULL,
  itemname TEXT NOT NULL,
  description TEXT NOT NULL,
  create_date DATETIME NOT NULL,
  update_date DATETIME,
  room TEXT,
  owner TEXT,
  finder TEXT,
  status SET("found","lost","claimed") NOT NULL,
  PRIMARY KEY(id)
);
#Inserting all the campus buildings into locations table
INSERT INTO locations(create_date,update_date,name)
VALUES (NOW( ),NOW( ),"Hancock Building"),(NOW( ),NOW( ),"Dyson Building"),(NOW( ),NOW( ),"Lowell-Thomas Building"),(NOW( ),NOW( ),"Donnelly Building"),(NOW( ),NOW( ),"Fontaine Building");

#Inserting Demo Data into table stuff
INSERT INTO stuff(id,location_id, itemname, description, create_date,update_date,room,owner,finder,status)
VALUES ("1","Hancock Building","Wallet","Brown has 100 dollars","2022-10-27 12:43:12",NOW( ), "1021", "Kevin","Andrew", "Lost"),
       ("2","Dyson Building","Phone","Red Case, iPhone 10","2022-10-28 10:11:34",NOW( ), "Lobby", "Steve","Kevin", "Lost"),
       ("3","Dyson Building","Laptop","Dell Laptop, Silver","2022-10-28 12:01:22",NOW( ), "Lobby", "Amanda","Steve", "Lost");

INSERT INTO stuff(id,location_id,itemname,description, create_date,update_date,room,owner,finder,status)
VALUES ("4","Dyson Building","Sneakers","Red and Blue Nike Size 10","2022-10-29 01:01:00",NOW( ), "111", "Bob","Andrew", "Found"),
       ("5","Fontaine Building","Bookbag","Brown Nike Bookbag","2022-10-29 02:45:12",NOW( ), "221", "Nolan","Kai", "Found"),
       ("6","Hancock Building","Keys","Gold really small","2022-10-29 12:22:22",NOW( ), "3003", "Andrew","Chase", "Found");

EXPLAIN users;
EXPLAIN stuff;
EXPLAIN locations;

SELECT * FROM users;
SELECT * FROM stuff;
SELECT * FROM locations;

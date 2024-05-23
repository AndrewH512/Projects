# Nascar Tables
# Authors: Andrew Hennessy

# 1.) Creating the Tables
create database if not exists nascar_db;
USE nascar_db;
DROP TABLE IF EXISTS Users;
CREATE TABLE IF NOT EXISTS Users
(
  UserID INT unique auto_increment,
  UserName TEXT not null,
  UserPassword TEXT not null
);
DROP TABLE IF EXISTS Stats_List;
CREATE TABLE IF NOT EXISTS Stats_List
(
  ListID INT unique auto_increment,
  List_Driver TEXT not null,
  List_Team TEXT not null,
  List_All_Time TEXT not null,
  List_Records TEXT not null
);
DROP TABLE IF EXISTS DriverList;
CREATE TABLE IF NOT EXISTS DriverList
(
  Driver_ID INT unique auto_increment,
  Driver_Name TEXT not null
);
DROP TABLE IF EXISTS Team_List;
CREATE TABLE IF NOT EXISTS Team_List
(
  Team_ID INT unique auto_increment,
  Team_Name TEXT not null
);
DROP TABLE IF EXISTS Team_Stats_Basic_Info;
CREATE TABLE IF NOT EXISTS Team_Stats_Basic_Info
(
  Team_ID INT unique auto_increment,
  Team_Name TEXT not null,
  Team_Birthday INT not null,
  Team_Owner TEXT not null
);
DROP TABLE IF EXISTS Team_Stats_Laps;
CREATE TABLE IF NOT EXISTS Team_Stats_Laps
(
  Team_ID INT unique auto_increment,
  Team_leadlap INT not null,
  Team_lapslead INT not null,
  Team_laps INT not null,
  Team_dnfs INT not null
);
DROP TABLE IF EXISTS Team_Stats_Achivements;
CREATE TABLE IF NOT EXISTS Team_Stats_Achivements
(
  Team_ID INT unique auto_increment,
  Team_year INT not null,
  Team_wins INT not null,
  Team_topfives INT not null,
  Team_toptens INT not null
);
DROP TABLE IF EXISTS Team_Stats_Averages;
CREATE TABLE IF NOT EXISTS Team_Stats_Averages
(
  Team_ID INT unique auto_increment,
  Team_avgfinish INT not null,
  Team_avgstart INT not null,
  Team_avgled TEXT not null,
  Team_winpercetange TEXT not null
);
DROP TABLE IF EXISTS All_Time_List;
CREATE TABLE IF NOT EXISTS All_Time_List
(
  All_ID INT unique auto_increment,
  All_Team TEXT not null,
  All_Driver TEXT not null
);

DROP TABLE IF EXISTS Team_Stats_All_Time;
CREATE TABLE IF NOT EXISTS Team_Stats_All_Time
(
  All_TeamID INT unique auto_increment,
  Team_Name TEXT not null,
  Team_Wins INT not null,
  Team_Topfives INT not null,
  Team_TopTens INT not null,
  Team_Retired TEXT not null
);

DROP TABLE IF EXISTS Driver_Stats_All_Time;
CREATE TABLE IF NOT EXISTS Driver_Stats_All_Time
(
  All_DriverID INT unique auto_increment,
  Driver_Name TEXT not null,
  Driver_Wins INT not null,
  Driver_Topfives INT not null,
  Driver_TopTens INT not null,
  Driver_Retired TEXT not null
);


DROP TABLE IF EXISTS Nascar_All_Time_Records;
CREATE TABLE IF NOT EXISTS Nascar_All_Time_Records
(
  Records_ID INT unique auto_increment,
  Records_Wins INT not null,
  Record_Topfives INT not null,
  Record_Toptens INT not null,
  Record_LapsLed INT not null,
  Record_Year INT not null
);

DROP TABLE IF EXISTS Driver_Stats_Basic_Info;
CREATE TABLE IF NOT EXISTS Driver_Stats_Basic_Info
(
  Driver_ID INT unique auto_increment,
  Driver_Birthday TEXT not null,
  Driver_Age INT not null
);

DROP TABLE IF EXISTS Driver_Stats_Laps;
CREATE TABLE IF NOT EXISTS Driver_Stats_Laps
(
  Driver_ID INT unique auto_increment,
  Driver_leadlap INT not null,
  Driver_lapslead INT not null,
  Driver_laps INT not null,
  Driver_dnfs INT not null
);

DROP TABLE IF EXISTS Driver_Stats_Achivements;
CREATE TABLE IF NOT EXISTS Driver_Stats_Achivements
(
  Driver_ID INT unique auto_increment,
  Driver_Year TEXT not null,
  Driver_wins INT not null,
  Driver_topfives INT not null,
  Driver_toptens INT not null
);

DROP TABLE IF EXISTS Driver_Stats_Averages;
CREATE TABLE IF NOT EXISTS Driver_Stats_Averages
(
  Driver_ID INT unique auto_increment,
  Driver_AvgFinish INT not null,
  Driver_AvgStart INT not null,
  Driver_AvgLed TEXT not null,
  Driver_WinPercetange TEXT not null
);

# 2) Inserting 
#Insert Data Into the Table
#Users Table
INSERT INTO Users(UserName,UserPassword)
VALUES ("Andrew","Blue"), ("Steve","Purple"), ("Bob", "Green"), ("Zach","Brown");

#Stats List Table
INSERT INTO Stats_List(List_Driver,List_Team, List_All_Time, List_Records)
VALUES ("2022 Personal Driver Stats List", "2022 Team Stats", "2022 All Time Stats", "2022 All Time Records"),("2021 Personal Driver Stats List", "2021 Team Stats", "2021 All Time Stats", "2021 All Time Records"),("2020 Personal Driver Stats List", "2020 Team Stats", "2020 All Time Stats", "2020 All Time Records"),("2019 Personal Driver Stats List", "2019 Team Stats", "2019 All Time Stats", "2019 All Time Records");

#Team Stats Inserts
#Team_List Table
INSERT INTO Team_List(Team_Name)
VALUES ("Joe Gibbs Racing"),("Team Penske"),("23XI Racing"),("Hendrick Motorsports");

#Team_Stats_Basic_Info
INSERT INTO Team_Stats_Basic_Info(Team_Name, Team_Birthday, Team_Owner)
VALUES ("Joe Gibbs Racing","1992","Joe Gibbs"),("Team Penske", "1973", "Roger Penske"),("23XI Racing","2020", "Denny Hamlin"),("Hendrick Motorsports", "1985", "Rick Hendrick");

#Team_Stats_Laps
INSERT INTO Team_Stats_Laps(Team_leadlap,Team_lapslead,Team_laps,Team_dnfs)
VALUES ("109","2396","35229","35"),("79","1506","26762","29"),("42","333","17080","30"),("105","2375","34777","39");


#Team_Stats_Achievemnts
INSERT INTO Team_Stats_Achivements(Team_Year, Team_wins, Team_topfives, Team_toptens)
VALUES ("2022","6","34","68"), ("2022","5","28","43"), ("2022","2","10","19"), ("2022","11","34","62");

#Team_Stats_Averages
INSERT INTO Team_Stats_Averages(Team_avgfinish, Team_avgstart, Team_avgled, Team_winpercetange)
VALUES ("15","13","6%","4%"),("14","11","4%","4%"), ("21","15","2%","2%"),("14","14","6%","7%");

#All Time Stats Inserts
#All_Time_List
INSERT INTO All_Time_List(All_Team, All_Driver)
VALUES ("Chevy Teams", "Chevy Drivers"),("Ford Teams", "Ford Drivers"),("Dodge Teams","Dodge Drivers"),("Toytoa Teams","Toytoa Drivers");

#Team_Stats_All_Time
INSERT INTO Team_Stats_All_Time(Team_Name, Team_Wins,Team_Topfives,Team_TopTens,Team_Retired)
VALUES ("Joe Gibbs Racing","201","863","1428","Active"),("Team Penske","136","632","1060","Active"),("23XI Racing","4","18","27","Active"),("Hendrick Motorsports","294","1201","2060","Active");

#Driver_Stats_All_Time
INSERT INTO Driver_Stats_All_Time (Driver_Name, Driver_Wins, Driver_Topfives, Driver_TopTens, Driver_Retired)
VALUES ("Richard Petty","200","555","712","Retired"),("Jeff Gordon","93","325","477","Retired"),("Kevin Harvick","60","248","435","Active"),("Jimmie Johnson","83","232","374","Retired");

#Nascar_All_Time_Records
INSERT INTO Nascar_All_Time_Records(Records_Wins, Record_Topfives, Record_Toptens, Record_LapsLed, Record_Year)
VALUES ("27","38","40","5534","1967"),("10","20","26","2581","2021"),("13","26","28","1717","1998"),("11","21","24","3357","1987");

#Driver Stats Inserts
#DriverList
INSERT INTO DriverList(Driver_Name)
VALUES ("Kyle Busch"),("Ryan Blaney"),("Bubba Wallace"),("Chase Elliott");

#Driver_Stats_Basic_Info
INSERT INTO Driver_Stats_Basic_Info(Driver_Birthday,Driver_Age)
VALUES ("May 2 1985", "37"),("Decemeber 31 1993", "29"),("October 8 1993", "29"), ("November 28 1995", "27");

#Driver_Stats_Laps;
INSERT INTO Driver_Stats_Laps(Driver_leadlap,Driver_lapslead, Driver_laps, Driver_dnfs)
VALUES ("27","627","8479","9"), ("28","636","8891","8"),("19","150","8550","16"),("29","857","8824","7");

#Driver_Stats_Achivements;
INSERT INTO Driver_Stats_Achivements(Driver_Year, Driver_wins, Driver_topfives, Driver_toptens)
VALUES ("2022","1","8","17"), ("2022","0","12","17"),("2022","1","5","10"), ("2022","5","12","20");

#Driver_Stats_Averages;
INSERT INTO Driver_Stats_Averages(Driver_AvgFinish, Driver_AvgStart, Driver_AvgLed, Driver_WinPercetange)
VALUES ("16.7","14.1","6%","2%"), ("13.6","10.1","6%","0%"), ("18.3","18.4","1%","2%"), ("12.5","10.7","9%","14%");


#Exlaining Each table
Explain Users;


Explain Stats_List;

Explain Team_List;
Explain Team_Stats_Basic_Info;
Explain Team_Stats_Laps;
Explain Team_Stats_Achivements;
Explain Team_Stats_Averages;

Explain All_Time_List;
Explain Team_Stats_All_Time;
Explain Driver_Stats_All_Time;
Explain Nascar_All_Time_Records;

Explain DriverList;
Explain Driver_Stats_Basic_Info;
Explain Driver_Stats_Laps;
Explain Driver_Stats_Achivements;
Explain Driver_Stats_Averages;


#Showing the Data
Select * FROM Users;
Select * FROM Stats_List;

Select * FROM Team_List;
Select * FROM Team_Stats_Basic_Info;
Select * FROM Team_Stats_laps;
Select * FROM Team_Stats_Achivements;
Select * FROM Team_Stats_Averages;

Select * FROM All_Time_List;
Select * FROM Team_Stats_All_Time;
Select * FROM Driver_Stats_All_Time;
Select * FROM Nascar_All_Time_Records;

Select * FROM DriverList;
Select * FROM Driver_Stats_Basic_Info;
Select * FROM Driver_Stats_Laps;
Select * FROM Driver_Stats_Achivements;
Select * FROM Driver_Stats_Averages;



# 3). Examples of the queries: INNER JOIN, OUTER JOIN, sub-query, and corrlated sub-query
#Inner Join
SELECT  Driver_Stats_Laps.Driver_ID,  Driver_Stats_Laps.Driver_lapslead,  Driver_Stats_Laps.Driver_laps
FROM Driver_Stats_Laps
INNER JOIN Driver_Stats_Achivements
ON  Driver_Stats_Laps.Driver_ID = Driver_Stats_Achivements.Driver_ID;

#Outer Join
SELECT * FROM Driver_Stats_Basic_Info
LEFT JOIN Driver_Stats_Achivements ON Driver_Stats_Basic_Info.Driver_ID = Driver_Stats_Achivements.Driver_ID;

#non-corrlated sub-query
SELECT Driver_AvgStart
FROM Driver_Stats_Averages 
WHERE Driver_AvgStart < 
(
	SELECT AVG(Driver_AvgFinish)
	FROM Driver_Stats_Averages
);

#corrlated sub-query
SELECT Driver_AvgStart, Driver_AvgLed
FROM Driver_Stats_Averages 
WHERE Driver_AvgStart > 
(
	SELECT AVG(Driver_AvgLed)
	FROM Driver_Stats_Averages 
	WHERE Driver_AvgStart > Driver_AvgLed
)
ORDER BY Driver_AvgStart DESC;




CREATE SCHEMA TRIPSHARE;
USE TRIPSHARE;

DROP TABLE IF EXISTS COUNTRY;
CREATE TABLE COUNTRY(
C_name VARCHAR(50),
Travel_advisory VARCHAR(100),
PRIMARY KEY (C_name)
);

DROP TABLE IF EXISTS MEMBER;
CREATE TABLE MEMBER(
Username VARCHAR(30),
Password VARCHAR(40) NOT NULL,
Email VARCHAR(100) NOT NULL,
C_name VARCHAR(50),
S_name VARCHAR(50),
City_name VARCHAR(50),
Street_name VARCHAR(50),
Ranking INT UNSIGNED NOT NULL DEFAULT 0,
Is_suspended BOOLEAN DEFAULT FALSE,
Member_type SET('Normal', 'Privileged') NOT NULL,
Credibility_score INT DEFAULT 0,
PRIMARY KEY (Username),
FOREIGN KEY (C_name)
        REFERENCES COUNTRY(C_name)
        ON UPDATE CASCADE
        ON DELETE CASCADE,
CHECK (LENGTH(Username) > 5)
);
DROP TABLE IF EXISTS DESTINATION;
CREATE TABLE DESTINATION(
Dest_name VARCHAR(50),
C_name VARCHAR(50),
S_name VARCHAR(50),
City_name VARCHAR(50),
Street_name VARCHAR(50),
Description TEXT,
Rating TINYINT UNSIGNED DEFAULT 0,
Phone_number VARCHAR(20),
Hours_of_operation TEXT,
Destination_type SET('Sight', 'Restaurant', 'Mall') NOT NULL,
Link TEXT,
Ticket_price FLOAT(8,2),
Price_range TEXT,
Restaurant_type VARCHAR(50),
PRIMARY KEY (Dest_name, C_name, S_name, City_name, Street_name),
FOREIGN KEY (C_name)
REFERENCES COUNTRY(C_name)
ON UPDATE CASCADE
ON DELETE CASCADE,
CHECK (LENGTH(Phone_number) >= 7)
);
DROP TABLE IF EXISTS COMMENT;
CREATE TABLE COMMENT(
Comment_id CHAR(12),
Post_time TIME,
Total_likes INT UNSIGNED DEFAULT 0,
Post_date DATE,
Content TEXT NOT NULL,
Member_id VARCHAR(30),
Commenting_on VARCHAR(50),
PRIMARY KEY (Comment_id),
FOREIGN KEY (Member_id)
REFERENCES MEMBER(Username)
ON UPDATE CASCADE
ON DELETE CASCADE,
FOREIGN KEY (Commenting_on)
REFERENCES DESTINATION(Dest_name)
ON UPDATE CASCADE
ON DELETE CASCADE
);
DROP TABLE IF EXISTS IMAGE;
CREATE TABLE IMAGE(
Image_id CHAR(12),
Image_link VARCHAR(500) UNIQUE,
Alt_text TEXT,
Member_id VARCHAR(30),
PRIMARY KEY (Image_id),
FOREIGN KEY (Member_id)
REFERENCES MEMBER(Username)
ON UPDATE CASCADE
ON DELETE CASCADE
);
DROP TABLE IF EXISTS PLAN;
CREATE TABLE PLAN(
Plan_id CHAR(12),
Name VARCHAR(50) NOT NULL,
Rating TINYINT UNSIGNED DEFAULT 0,
Purpose TEXT,
Visibility SET('Public', 'Private'),
Start_date DATE,
End_date DATE,
Member_id VARCHAR(30),
PRIMARY KEY (Plan_id),
FOREIGN KEY (Member_id)
REFERENCES MEMBER(Username)
ON UPDATE CASCADE
ON DELETE CASCADE,
CHECK (Rating <= 10)
);
DROP TABLE IF EXISTS BUSINESS_OWNER;
CREATE TABLE BUSINESS_OWNER(
Phone_number VARCHAR(20),
Is_verified BOOLEAN NOT NULL,
Contact_person VARCHAR(50),
F_name VARCHAR(20) NOT NULL,
L_name VARCHAR(30) NOT NULL,
B_type VARCHAR(50),
PRIMARY KEY (Phone_number),
CHECK (LENGTH(Phone_number) >= 7)
);
DROP TABLE IF EXISTS REVIEWS;
CREATE TABLE REVIEWS(
Plan_id CHAR(12),
Member_id VARCHAR(30),
Review TINYINT UNSIGNED NOT NULL,
PRIMARY KEY (Plan_id, Member_id),
FOREIGN KEY (Plan_id)
REFERENCES PLAN(Plan_id)
ON UPDATE CASCADE
ON DELETE CASCADE,
FOREIGN KEY (Member_id)
REFERENCES MEMBER(Username)
ON UPDATE CASCADE
ON DELETE CASCADE,
CHECK (Review <= 10)
);
DROP TABLE IF EXISTS RATES;
CREATE TABLE RATES(
Dest_id VARCHAR(50),
Member_id VARCHAR(30),
Rating TINYINT UNSIGNED NOT NULL,
PRIMARY KEY (Dest_id, Member_id),
FOREIGN KEY (Member_id)
REFERENCES MEMBER(Username)
ON UPDATE CASCADE
ON DELETE CASCADE,
FOREIGN KEY (Dest_id)
REFERENCES DESTINATION(Dest_name)
ON UPDATE CASCADE
ON DELETE CASCADE,
CHECK (RATING <= 10)
);
DROP TABLE IF EXISTS LIKES;
CREATE TABLE LIKES(
Comment_id CHAR(12),
Member_id VARCHAR(30),
Likes INT UNSIGNED NOT NULL,
PRIMARY KEY (Comment_id, Member_id),
FOREIGN KEY (Comment_id)
REFERENCES COMMENT(Comment_id)
ON UPDATE CASCADE
ON DELETE CASCADE,
FOREIGN KEY (Member_id)
REFERENCES MEMBER(Username)
ON UPDATE CASCADE
ON DELETE CASCADE
);
DROP TABLE IF EXISTS EDITS;
CREATE TABLE EDITS(
Dest_id VARCHAR(50),
Member_id VARCHAR(30),
Modified_date DATE NOT NULL,
PRIMARY KEY (Dest_id, Member_id),
FOREIGN KEY (Member_id)
REFERENCES MEMBER(Username)
ON UPDATE CASCADE
ON DELETE CASCADE,
FOREIGN KEY (Dest_id)
REFERENCES DESTINATION(Dest_name)
ON UPDATE CASCADE
ON DELETE CASCADE
);
DROP TABLE IF EXISTS MANAGES;
CREATE TABLE MANAGES(
Business_owner_id VARCHAR(15),
Dest_id VARCHAR(50),
PRIMARY KEY (Business_owner_id, Dest_id),
FOREIGN KEY (Dest_id)
REFERENCES DESTINATION(Dest_name)
ON UPDATE CASCADE
ON DELETE CASCADE,
FOREIGN KEY (Business_owner_id)
REFERENCES BUSINESS_OWNER(Phone_number)
ON UPDATE CASCADE
ON DELETE CASCADE
);
DROP TABLE IF EXISTS FOLLOWING;
CREATE TABLE FOLLOWING(
Follower_id VARCHAR(30),
Following_id VARCHAR(30),
PRIMARY KEY (Follower_id, Following_id),
FOREIGN KEY (Follower_id)
REFERENCES MEMBER(Username)
ON UPDATE CASCADE
ON DELETE CASCADE,
FOREIGN KEY (Following_id)
REFERENCES MEMBER(Username)
ON UPDATE CASCADE
ON DELETE CASCADE
);
DROP TABLE IF EXISTS REPLIES_TO;
CREATE TABLE REPLIES_TO(
Comment_id CHAR(12),
Member_id VARCHAR(30),
Reply TEXT NOT NULL,
PRIMARY KEY (Comment_id, Member_id),
FOREIGN KEY (Comment_id)
REFERENCES COMMENT(Comment_id)
ON UPDATE CASCADE
ON DELETE CASCADE,
FOREIGN KEY (Member_id)
REFERENCES MEMBER(Username)
ON UPDATE CASCADE
ON DELETE CASCADE
);
DROP TABLE IF EXISTS WAYS_OF_TRAVEL;
CREATE TABLE WAYS_OF_TRAVEL(
Dest_id VARCHAR(50),
Travel_type VARCHAR(50),
PRIMARY KEY (Dest_id, Travel_type),
FOREIGN KEY (Dest_id)
REFERENCES DESTINATION(Dest_name)
ON UPDATE CASCADE
ON DELETE CASCADE
);
DROP TABLE IF EXISTS BUSINESS_NAME;
CREATE TABLE BUSINESS_NAME(
Business_owner_id VARCHAR(15),
B_name VARCHAR(50),
PRIMARY KEY (Business_owner_id, B_name),
FOREIGN KEY (Business_owner_id)
REFERENCES BUSINESS_OWNER(Phone_number)
ON UPDATE CASCADE
ON DELETE CASCADE
);
DROP TABLE IF EXISTS ASSOCIATED_STORES;
CREATE TABLE ASSOCIATED_STORES(
Business_owner_id VARCHAR(15),
Associated_store VARCHAR(50),
PRIMARY KEY (Business_owner_id, Associated_store),
FOREIGN KEY (Business_owner_id)
REFERENCES BUSINESS_OWNER(Phone_number)
ON UPDATE CASCADE
ON DELETE CASCADE
);
DROP TABLE IF EXISTS ASSOCIATED_MEMBERS;
CREATE TABLE ASSOCIATED_MEMBERS(
Plan_id CHAR(12),
Member_id VARCHAR(30),
PRIMARY KEY (Plan_id, Member_id),
FOREIGN KEY (Plan_id)
REFERENCES PLAN(Plan_id)
ON UPDATE CASCADE
ON DELETE CASCADE,
FOREIGN KEY (Member_id)
REFERENCES MEMBER(Username)
ON UPDATE CASCADE
ON DELETE CASCADE
);
DROP TABLE IF EXISTS ATTRACTIONS;
CREATE TABLE ATTRACTIONS(
Plan_id CHAR(12),
Attraction_name VARCHAR(50),
Arrival DATETIME,
Departure DATETIME,
PRIMARY KEY (Plan_id, Attraction_name),
FOREIGN KEY (Plan_id)
REFERENCES PLAN(Plan_id)
ON UPDATE CASCADE
ON DELETE CASCADE
);
DROP TABLE IF EXISTS SHOPS;
CREATE TABLE SHOPS(
Dest_id VARCHAR(50),
Shop_name VARCHAR(50),
PRIMARY KEY (Dest_id, Shop_name),
FOREIGN KEY (Dest_id)
REFERENCES DESTINATION(Dest_name)
ON UPDATE CASCADE
ON DELETE CASCADE
);
/*Here are some example of some insert statements for the tables*/
INSERT INTO COUNTRY VALUES('United States', 'Hurricane Warning');

INSERT INTO COUNTRY (C_name) VALUES
('Canada'),
('Mexico'),
('England'),
('Italy'),
('France'),
('China'),
('Russia'),
('Japan');

INSERT INTO MEMBER VALUES
('John180', '15@GolfPro', 'JohnSmith180@gmail.com','Canada','Quebec', 'Quebec
City', '456Street', 100, null, 'Normal', null),
('Sally7920', '2017#Basic', 'SallyThomas@gmail.com', 'Mexico','Jalisco', 'Puerto
Vallarta', 'PurpleRd', 250, False, 'Normal', 0),
('10Jessica', '1Baker$@4178', 'JessicaI@gmail.com', 'United States','Texas',
'Tyler', 'FifthSt', 0, True, 'Privileged', 100),
('Richard5', 'Base*ballFan900', 'Richie@gmail.com', 'United States','Illinois',
'Chicago', 'NonelectricAve', 50, False, 'Normal', 200),
('Lucas76', 'RedSocks!76', 'Lucas@gmail.com', 'France','Nouvelle-Aquitaine',
'Bordeaux', 'GrassSt', 60, True, 'Privileged', -500),
('TedDBear', 'Group7Rocks!', 'Teddbear@yahoo.com', 'China','Hainan', 'Sanya',
'MountainSt', 70, FALSE, 'Privileged',
1000000),
('CraigBond007', 'DNJGFvins3!', 'Bondboy@hotmail.com', 'England', 'Yorkshire', 
'Bradford', 'CrimeSt', 40, FALSE, 'Privileged', 1000);

INSERT INTO DESTINATION VALUES
('ArtMuseum', 'United States', 'Florida', 'Destin', '123Street', 'A museum with
different types of art with unique mediums', NULL, '9035231232', 'MWF at 8am to
6pm', 'Sight', 'exampleWebsite.org', 15.85, NULL, NULL);
INSERT INTO DESTINATION(Dest_name, C_name, S_name, City_name, Street_name,
Destination_type)
VALUES('American Mall', 'United States', 'Texas', 'Tyler', '3901 Broadway St.',
'Mall');

INSERT INTO DESTINATION VALUES
('Eiffel Tower', 'France', 'Île-de-France', 'Paris', 'Champ de Mars', 'Iconic iron
lattice tower offering city views', 10, '+33 144112300', '9:30 AM - 11:45 PM',
'Sight', 'toureiffel.paris', 25.00, NULL, NULL),
('La Tour Argent', 'France', 'Île-de-France', 'Paris', 'Quai de la Tournelle',
'Upscale restaurant with classic French cuisine', 4, '+33 143542331', '12:00 PM -
2:30 PM, 7:00 PM - 10:00 PM', 'Restaurant', 'tourdargent.com/en/', NULL, '100.00-
200.00', 'French Cuisine'),
('New York Pizza Palor', 'United States', 'New York', 'New York City', '123 Jockey Ln.', 
'The best pizza palor in New York City', 9, '+1 212-736-3465', '12:00 PM - 9:00 PM', 
'Restaurant', 'NYPP.com', NULL, '14.99-29.99', 'Italian'),
('Statue of Liberty', 'United States', 'New York', 'New York City', 'Liberty
Island', 'Iconic statue representing freedom & democracy', 5, '+1 212-363-3200',
'9:30 AM - 5:00 PM', 'Sight', 'nps.gov', 18.00, NULL, NULL),
('Grand Canyon', 'United States', 'Arizona', 'Grand Canyon Village', 'Arizona ln.',
'Huge canyon known for its colorful landscape', 5, '+1 928-638-7888', '24 hours',
'Sight', 'nps.gov', 35.00, NULL, NULL),
('Empire State Building', 'United States', 'New York', 'New York City', '350 5th
Ave', 'Iconic skyscraper offering observatory decks', 4, '+1 212-736-3100', '8:00
AM - 2:00 AM', 'Sight', 'esbnyc.com', 38.00, NULL, NULL),
('Mall of America', 'United States', 'Minnesota', 'Bloomington', '2131 Lindau Ln',
'The biggest mall in the world', 9, '+1 952-883-8800', '11:00 AM - 8:00 PM',
'Mall', NULL, NULL, NULL, NULL),
('Colosseum', 'Italy', 'Lazio', 'Rome', 'Piazza del Colosseo', 'Iconic amphitheater
with guided tours', 5, '+39 0639967700', '8:30 AM - 7:00 PM', 'Sight',
'coopculture.it', 16.00, NULL, NULL),
('Trevi Fountain', 'Italy', 'Lazio', 'Rome', 'Piazza di Trevi', 'Baroque fountain &
landmark coin tossing', 4, NULL, '24 hours', 'Sight', NULL, 0.00, NULL, NULL),
('Rialto Market', 'Italy', 'Veneto', 'Venice', 'San Polo', 'Historic market with
fresh produce & seafood', 4, '+39 0412437635', '7:30 AM - 1:30 PM', 'Sight', NULL,
0.00, NULL, NULL),
('Shanghai Tower', 'China', 'Shanghai', 'Shanghai', '501 Yincheng Middle Rd',
'Tallest skyscraper with observation decks', 5, '+86 2120656999', '8:30 AM - 10:00
PM', 'Sight', 'shanghaitower.com', 40.00, NULL, NULL),
('Forbidden City', 'China', 'Beijing', 'Beijing', '4 Jingshan Front St', 'Ancient
imperial palace complex with tours', 5, '+86 1085007421', '8:30 AM - 5:00 PM',
'Sight', 'en.dpm.org', 10.00, NULL, NULL),
('The Bund', 'China', 'Shanghai', 'Shanghai', 'Zhongshan East 1st Rd', 'Historic
waterfront area with colonial buildings', 4, NULL, '24 hours', 'Sight', NULL, 0.00,
NULL, NULL),
('Mount Hakodate Ropeway', 'Japan', 'Hokkaido', 'Hakodate', '19-7 Motomachi', 
'Scenic ropeway offering panoramic views of Hakodate and the surrounding area', 8, '+81 138-23-3105', 
'9:00 AM - 10:00 PM', 'Sight', 'hakodate.travel/en', 1200.00, NULL, NULL),
('Hirosaki Castle', 'Japan', 'Tohoku', 'Hirosaki', '1 Shimoshiroganecho', 
'Historic castle with cherry blossoms and surrounding park', 8, '+81 172-33-8739', 
'9:00 AM - 5:00 PM', 'Sight', 'hirosakipark.or.jp', 310.00, NULL, NULL),
('Tokyo Disneyland', 'Japan', 'Kanto', 'Urayasu', '1-1 Maihama', 
'Famous theme park with rides, shows, and Disney characters', 9, '+81 45-330-5211', 
'8:00 AM - 10:00 PM', 'Sight', 'tokyodisneyresort.jp', 8200.00, NULL, NULL),
('Matsumoto Castle', 'Japan', 'Chubu', 'Matsumoto', '4-1 Marunouchi', 
'Historic castle with black walls and a museum', 8, '+81 263-32-2902', 
'8:30 AM - 5:00 PM', 'Sight', 'matsumoto-castle.jp', 610.00, NULL, NULL),
('Osaka Castle', 'Japan', 'Kansai', 'Osaka', '1-1 Osakajo', 
'Historic castle with a museum, gardens, and panoramic views', 8, '+81 6-6941-3044', 
'9:00 AM - 5:00 PM', 'Sight', 'osakacastle.net', 600.00, NULL, NULL),
('Itsukushima Shrine', 'Japan', 'Chugoku', 'Hatsukaichi', '1-1 Miyajimacho', 
'Shinto shrine known for its "floating" torii gate', 9, '+81 829-44-2020', 
'6:30 AM - 6:00 PM', 'Sight', 'itsukushimajinja.jp', 0.00, NULL, NULL),
('Ritsurin Garden', 'Japan', 'Shikoku', 'Takamatsu', '1-20-16 Ritsurinchuo', 
'Historic garden featuring ponds, bridges, and tea houses', 8, '+81 87-833-7411', 
'9:00 AM - 5:00 PM', 'Sight', 'ritsuringarden.jp', 410.00, NULL, NULL),
('Nagasaki Peace Park', 'Japan', 'Kyushu', 'Nagasaki', '7-8 Hirano-machi', 
'Park dedicated to peace and remembrance of the atomic bombing', 9, '+81 95-844-1231', 
'8:30 AM - 5:30 PM', 'Sight', 'nagasakipeace.jp', 0.00, NULL, NULL),
('Times Square Bistro', 'United States', 'New York', 'New York City', '123 Times Square Ave',
'Cozy bistro offering a variety of international cuisine in the heart of Times Square.', 7, 
'+1 212-123-4567', '11:00 AM - 11:00 PM', 'Restaurant', 'timessquarebistro.com', NULL, 
'22.00-37.00', 'International Cuisine'),
('Central Park Cafe', 'United States', 'New York', 'New York City', '45 Central Park West', 
'Charming cafe with outdoor seating serving fresh salads, sandwiches, and coffee near Central Park.', 
8, '+1 212-987-6543', '8:00 AM - 7:00 PM', 'Restaurant', 'centralparkcafe.com', NULL, '4.98-13.98', 'Cafe'),
('Empire Steakhouse', 'United States', 'New York', 'New York City', '34 W 35th St', 
'Upscale steakhouse offering premium cuts of beef and seafood in a refined setting near the Empire State Building.', 
9, '+1 212-876-5432', '5:00 PM - 11:00 PM', 'Restaurant', 'empiresteakhouse.com', NULL, '48.00-145.00', 'Steakhouse'),
('Little Italy Trattoria', 'United States', 'New York', 'New York City', '78 Mulberry St', 
'Authentic Italian trattoria serving traditional pasta dishes and wood-fired pizzas in the heart of Little Italy.', 
8, '+1 212-345-6789', '12:00 PM - 10:00 PM', 'Restaurant', 'littleitalytrattoria.com', NULL, '25.00-75.00', 'Italian'),
('Chinatown Dumpling House', 'United States', 'New York', 'New York City', '56 Mott St', 
'Casual eatery specializing in handcrafted dumplings and dim sum dishes in the bustling neighborhood of Chinatown.', 7, 
'+1 212-234-5678', '10:00 AM - 9:00 PM', 'Restaurant', 'chinatowndumplinghouse.com', NULL, '7.00-23.00', 'Chinese');

INSERT INTO COMMENT VALUES
('000000000001', '11:10:49', NULL, '2018-12-09', 'Very Good!', 'Sally7920',
'ArtMuseum'),
('000000000002', '4:10:49', NULL, '2018-12-09', 'The only thing more dead than the
concept of the mall is the American Dream', 'Sally7920', 'Mall of America'),
('000000000003', '6:10:09', NULL, '2024-04-09', 'Did not have any bunt cake',
'10Jessica', 'The Bund'),
('000000000004', '12:10:49', NULL, '2024-04-09', 'Why is called the forbidden city
if I can go to it?', '10Jessica', 'Forbidden City'),
('000000000005', '03:25:55', NULL, '2019-01-09', 'I hate being outside', 'Lucas76',
'Grand Canyon');

INSERT INTO PLAN VALUES
('111111000000', "FunfairPark", 4, 'Have a great time at this amusement park!',
'Public', '2018-12-09', '2024-04-10', 'John180'),
('111111000055', "Worst places to live in America", 4, 'Dont live here, if you live
here than I will insult you', 'Private', '2024-05-09', '2024-05-15', '10Jessica'),
('111118100000', "Top Secret Government Bases", 4, 'I sure hope my commander doesnt
find this.', 'Public', '2018-12-09', '2024-04-10', 'Lucas76'),
('111411000000', "Swim with the Dolphins!", 4, 'I have always wanted to swim with the dolphins!', 
'Private', '2024-06-09', '2024-06-10', 'Sally7920'),
('121111000000', "Hospitals specializing in Dolphin attacks", 4, 'Ouch', 'Public',
'2024-06-11', '2024-06-12', 'Sally7920'),
('111111000237', "Yummy Resturants in New York City", 5, 'Going to try the best resturants that New York City has to offer', 
'Private', '2018-12-17', '2024-03-23', 'TedDBear'),
('111111007365', 'Japan and China Trip', 8, 'Going to travel to every province in Japan and some sights in China',
'Public', '2024-04-01', '2024-04-15', 'CraigBond007'),
('121110000000', "All around Japan Trip", 4, 'Amazing!', 'Public',
'2024-07-14', '2024-07-15', 'Sally7920');


INSERT INTO IMAGE VALUES
('123456789102', 'mywebpage.com/4cbhu34aaf', 'Image of air', 'John180'),
('123456789103', 'google.com/4cboenaaf', 'Dog eating frisbee ', 'Sally7920'),
('123456789104', 'pumpkinstocks.com/8cbhef', 'Pumpkin Stock Prices', '10Jessica'),
('123456789105', 'mywebpage.com/4568401ea.', 'Image of Cat', 'John180'),
('123456789106', 'mywebpage.com/8ebhu34aaf', 'Picture of man holding a picture of a
fridge with a picture of a hamburger on it.', 'Lucas76');

INSERT INTO BUSINESS_OWNER VALUES
('9032438594', True, '9037428695', 'Charlie', 'Davis', 'Store'),
('9038675309', True, '9089423156', 'Mario', 'Mario', 'Plumber'),
('8002358451', False, '5619813655', 'Harold', 'Smith', 'Parking Lot'),
('9034215841', True, '1681635616', 'Hannah', 'Jann', 'Restaurant'),
('9532481594', True, '38196841645', 'Greg', 'Lou', 'Store');

INSERT INTO REVIEWS VALUES
('111111000000', 'Richard5', 7),
('111111000055', 'Lucas76', 8),
('111118100000', 'John180', 9),
('111411000000', 'Richard5', 2),
('111411000000', 'Sally7920', 3);

INSERT INTO RATES VALUES  
('Mall of America', 'Lucas76', 8),
('ArtMuseum', 'Richard5', 5),
('Grand Canyon', 'John180', 6),
('The Bund', 'Sally7920', 7),
('Forbidden City', 'Lucas76', 4);

INSERT INTO LIKES VALUES
('000000000001', 'Lucas76', 1),
('000000000002', 'John180', 1),
('000000000003', 'TedDBear', 1),
('000000000004', 'Sally7920', 1),
('000000000001', 'TedDBear', 1);

INSERT INTO EDITS VALUES
('ArtMuseum', 'TedDBear', '2024-04-11'),
('American Mall', '10Jessica', '2024-04-11'),
('Grand Canyon', '10Jessica', '2024-04-12'),
('Rialto Market', 'Lucas76', '2024-03-15'),
('The Bund', 'TedDBear', '2024-04-20');

INSERT INTO MANAGES VALUES 
('9032438594', 'ArtMuseum'),
('9038675309', 'American Mall'),
('8002358451', 'Grand Canyon'),
('9034215841', 'Rialto Market'),
('9032438594', 'New York Pizza Palor'),
('9532481594', 'The Bund');

INSERT INTO FOLLOWING VALUES
('10Jessica', 'TedDBear'),
('TedDBear', '10Jessica'),
('Richard5', 'TedDBear'),
('10Jessica', 'Sally7920'),
('Lucas76', '10Jessica');

INSERT INTO REPLIES_TO VALUES
('000000000001', 'Richard5', 'Why you lying!?'),
('000000000002', 'Sally7920', 'We should boycott this!'),
('000000000003', 'TedDBear', 'I will never eat here.'),
('000000000004', '10Jessica', 'Pumpkin Stocks in Bio.'),
('000000000005', 'Richard5', 'I liked this.');

INSERT INTO WAYS_OF_TRAVEL VALUES
('ArtMuseum', 'Car'),
('ArtMuseum', 'Plane'),
('ArtMuseum', 'Train'),
('Forbidden City', 'Car'),
('Forbidden City', 'Train');

INSERT INTO BUSINESS_NAME VALUES
('9032438594', 'BuyAndSell'),
('9038675309', 'Baked Beans'),
('8002358451', 'Just Tables!'),
('9034215841', 'Pumpkin Patch'),
('9532481594', 'McDonalds');

INSERT INTO ASSOCIATED_STORES VALUES
('9032438594','Walmart'),
('9038675309','Timmy Diner'),
('8002358451','Tyler Thrift'),
('9034215841','Hole in Wall'),
('9532481594','Tire Repair');

INSERT INTO ASSOCIATED_MEMBERS VALUES
('111111000000', 'John180'),
('111111000000', '10Jessica'),
('111118100000', '10Jessica'),
('111411000000', 'TedDBear'),
('121111000000', 'John180');

INSERT INTO ATTRACTIONS VALUES
('111111000000', 'ArtMuseum', '2024-02-14 03:56', '2024-02-14 06:17'),
('111111000055', 'Statue of Liberty', '2024-05-09 03:00', '2024-05-15 06:00'),
('111118100000', 'Grand Canyon', '2024-03-09 02:44', '2024-04-10 03:17'),
('111411000000', 'Mall of America', '2024-06-09 12:56', '2024-06-09 16:56'),
('111411000000', 'New York Pizza Palor', '2024-06-10 12:00', '2024-06-10 13:00'),
('111411000000', 'Chinatown Dumpling House', '2024-06-10 18:00', '2024-06-10 20:00'),
('121111000000', 'Mall of America', '2024-06-11 06:57', '2024-06-12 10:17'),
('121111000000', 'Eiffel Tower', '2024-08-12 11:00', '2024-08-12 11:59'),
('111111000000', 'Trevi Fountain', '2024-02-14 09:00', '2024-02-15 09:00'),
('111111000055', 'New York Pizza Palor', '2024-05-09 12:00', '2024-05-09 13:30'),
('111111000055', 'Empire Steakhouse', '2024-05-09 18:00', '2024-05-09 20:30'),
('111111007365', 'Hirosaki Castle', '2024-04-01 9:00', '2024-04-03 9:00'),
('111111007365', 'Itsukushima Shrine', '2024-04-03 17:00', '2024-04-03 19:00'),
('111111007365', 'Tokyo Disneyland', '2024-04-04 9:00', '2024-04-07 9:00'),
('111111007365', 'Matsumoto Castle', '2024-04-07 12:00', '2024-04-08 9:00'),
('111111007365', 'Mount Hakodate Ropeway', '2024-04-08 12:00', '2024-04-09 9:00'),
('111111007365', 'Nagasaki Peace Park', '2024-04-09 10:00', '2024-04-09 11:00'),
('111111007365', 'Osaka Castle', '2024-04-10 9:00', '2024-04-11 9:00'),
('111111007365', 'Ritsurin Garden', '2024-04-11 12:00', '2024-04-11 2:00'),
('111111007365', 'The Bund', '2024-04-12 7:00', '2024-04-12 9:00'),
('111111007365', 'Forbidden City', '2024-04-13 9:00', '2024-04-14 9:00'),
('111111000237', 'Times Square Bistro', '2024-03-17 12:00', '2024-03-17 13:00'),
('111111000237', 'Empire Steakhouse',   '2024-03-17 18:00', '2024-03-17 20:00'),
('111111000237', 'Central Park Cafe', '2024-03-18 06:00', '2024-03-18 06:30'),
('111111000237', 'New York Pizza Palor', '2024-03-18 12:00', '2024-03-17 13:00'),
('111111000237', 'Chinatown Dumpling House', '2024-03-18 17:30', '2024-03-17 19:30'),
('121110000000', 'Mount Hakodate Ropeway', '2024-07-14 06:23', '2024-07-15 10:18'),
('121110000000', 'Hirosaki Castle', '2024-01-23 09:34', '2024-01-25 12:30'),
('121110000000', 'Tokyo Disneyland', '2024-02-16 06:30', '2024-02-17 10:15'),
('121110000000', 'Matsumoto Castle', '2024-08-02 06:14', '2024-08-03 10:47'),
('121110000000', 'Itsukushima Shrine', '2024-08-03 10:14', '2024-08-04 12:45'),
('121110000000', 'Osaka Castle', '2024-03-17 14:34', '2024-03-18 11:12'),
('121110000000', 'Ritsurin Garden', '2024-06-11 06:57', '2024-06-12 10:17'),
('121110000000', 'Nagasaki Peace Park', '2024-06-11 06:57', '2024-06-12 10:17');

INSERT INTO SHOPS VALUES
('American Mall', 'ToysRUs'),
('Mall of America', 'Bloomington'),
('American Mall', 'Sephora'),
('Mall of America', 'Crocs'),
('Mall of America', 'H&M');

CREATE VIEW NEW_YORK_CITY_RESTAURANTS 
AS SELECT D.Dest_name AS Name, CONCAT(D.Street_name, ' ', D.City_name, ', ', D.S_name, ', ', D.C_name) AS Address, D.Price_range
    FROM DESTINATION D
    WHERE D.Destination_type = 'Restaurant' AND D.C_NAME = 'United States' AND D.City_name = 'New York City';

CREATE VIEW COUNTRIES_VISITED
AS SELECT M.Username, D.C_name AS Countries_Visited
    FROM PLAN P LEFT JOIN ASSOCIATED_MEMBERS A_M ON P.Plan_id = A_M.Plan_id
          INNER JOIN ATTRACTIONS A ON P.Plan_id = A.Plan_id 
          INNER JOIN DESTINATION D ON A.Attraction_name = D.Dest_name
          RIGHT JOIN MEMBER M ON (M.Username = P.Member_id OR M.Username = A_M.Member_id)
          ORDER BY M.Username;

CREATE VIEW JAPAN_TRIPS
AS SELECT P.Plan_id, D.Dest_name, D.C_name AS Country, D.S_name, D.City_name AS City
    FROM PLAN P INNER JOIN ATTRACTIONS A ON P.Plan_id = A.Plan_id
          INNER JOIN DESTINATION D ON A.Attraction_name = D.Dest_name
          WHERE D.C_name = 'Japan';


CREATE VIEW VISITED_COUNTRIES_WITH_USA 
AS SELECT DISTINCT M.Username, D.C_name AS Country
   FROM PLAN P LEFT JOIN ASSOCIATED_MEMBERS A_M ON P.Plan_id = A_M.Plan_id
        INNER JOIN ATTRACTIONS A ON P.Plan_id = A.Plan_id 
        INNER JOIN DESTINATION D ON A.Attraction_name = D.Dest_name
        RIGHT JOIN MEMBER M ON (M.Username = P.Member_id OR M.Username = A_M.Member_id)
   WHERE EXISTS (
       SELECT *
       FROM ATTRACTIONS A2 INNER JOIN PLAN P2 ON A2.Plan_id = P2.Plan_id
       INNER JOIN DESTINATION D2 ON A2.Attraction_name = D2.Dest_name
       WHERE D2.C_name = 'United States'
       AND ABS(DATEDIFF(A.Arrival, A2.Arrival)) <= 15
) AND D.C_NAME != 'United States'; -- It would be redundant to list the United States in this view.

CREATE VIEW PLAN_PRICES
AS SELECT P.Plan_id, M.Username, MIN(D.Ticket_price) AS Minimum_Cost, MAX(D.Ticket_price) AS Maximum_Cost, ROUND(AVG(D.Ticket_price), 2) AS Average_Price
   FROM PLAN P LEFT JOIN ASSOCIATED_MEMBERS A_M ON P.Plan_id = A_M.Plan_id
          INNER JOIN ATTRACTIONS A ON P.Plan_id = A.Plan_id 
          INNER JOIN DESTINATION D ON A.Attraction_name = D.Dest_name
          RIGHT JOIN MEMBER M ON (M.Username = P.Member_id OR M.Username = A_M.Member_id)
          WHERE Destination_type = 'Sight'
          GROUP BY P.Plan_id, M.Username
          ORDER BY P.Plan_id, M.Username;

CREATE VIEW JAPAN_STATES AS 
SELECT DISTINCT (S_name)
FROM DESTINATION
WHERE C_NAME = "Japan";

CREATE VIEW VISITED_STATES AS
SELECT M.Username, D.C_NAME, D.S_name
FROM (MEMBER M INNER JOIN PLAN P ON M.Username = P.Member_id) 
  INNER JOIN ATTRACTIONS A ON P.Plan_id = A.Plan_id 
  INNER JOIN DESTINATION D ON A.Attraction_name = D.Dest_name;

CREATE VIEW JAPAN_STATES_COUNT AS 
SELECT V.Username, COUNT(*) AS V_COUNT
FROM (JAPAN_STATES J JOIN VISITED_STATES V ON J.S_name = V.S_name)
GROUP BY V.Username;

CREATE VIEW RESTAURANT_OWNERS AS 
SELECT D.Dest_name AS restaurant_name, B.F_name AS first_name, B.L_name AS last_name, B.Contact_person AS contact_person, B.Phone_number AS phone, 
SUBSTRING(D.Price_range, LOCATE('-',D.Price_range) + LENGTH('-'), LENGTH(D.Price_range)) AS high_price_string
FROM DESTINATION D INNER JOIN MANAGES M ON D.Dest_name = M.Dest_id
INNER JOIN BUSINESS_OWNER B ON M.Business_owner_id = B.Phone_number
WHERE D.Destination_type = 'Restaurant';

-- Query 1
SELECT NYC.Name, NYC.Address, NYC.Price_range, 
COUNT(A.Attraction_name) AS Popularity
FROM PLAN P INNER JOIN ATTRACTIONS A ON P.Plan_id = A.Plan_id 
INNER JOIN NEW_YORK_CITY_RESTAURANTS NYC ON A.Attraction_name = 
NYC.Name
GROUP BY NYC.Name, NYC.Address, NYC.Price_range
ORDER BY Popularity DESC
LIMIT 3;


-- Query 2
SELECT M.Username, M.Member_type, M.Ranking, Count(I.Member_id)
FROM MEMBER M JOIN IMAGE I ON M.Username = I.Member_id
GROUP BY I.Member_id
HAVING COUNT(I.Member_id) = 
(SELECT MAX(Total_pictures)
 FROM (SELECT Count(I1.Member_id) AS Total_pictures
 FROM IMAGE I1
 GROUP BY I1.Member_id) AS max_pictures
);

-- Query 3
SELECT M.Username, M.C_name, M.S_name, M.City_name, M.Street_name, M.Ranking
FROM MEMBER M
WHERE M.Ranking IN (
SELECT MAX(M.Ranking) AS MostFollowers
FROM MEMBER M
GROUP BY M.C_Name
);


-- Query 4
SELECT DISTINCT M.Username, M.C_name AS 'Home Country'
FROM MEMBER M LEFT JOIN COUNTRIES_VISITED CV ON M.Username = CV.Username
WHERE LOCATE('United States', CV.Countries_Visited) = 0
AND M.Member_type = 'Privileged'
GROUP BY M.Username, M.C_Name
HAVING M.C_name != 'United States'
ORDER BY M.Username;

-- Query 5
SELECT DISTINCT Country FROM VISITED_COUNTRIES_WITH_USA;

-- Query 6a
SELECT restaurant_name, first_name, last_name, contact_person, phone, high_price_string
FROM RESTAURANT_OWNERS 
WHERE CAST(high_price_string AS decimal(5,2)) = 
       (SELECT MAX(high_price_string) FROM RESTAURANT_OWNERS);

-- Query 6b
SELECT B.F_name AS first_name, B.L_name AS last_name, 
    COUNT(DISTINCT A.Associated_store) + COUNT(DISTINCT M.Dest_id) + COUNT(DISTINCT BN.B_name) AS num_of_business
FROM BUSINESS_OWNER B 
LEFT JOIN MANAGES M ON B.Phone_number = M.Business_owner_id
LEFT JOIN ASSOCIATED_STORES A ON B.Phone_number = A.Business_owner_id
LEFT JOIN BUSINESS_NAME BN ON B.Phone_number = BN.Business_owner_id
GROUP BY B.Phone_number
HAVING num_of_business = (
    SELECT MAX(total_businesses)
    FROM (
        SELECT COUNT(DISTINCT A2.Associated_store) + COUNT(DISTINCT M2.Dest_id) + COUNT(DISTINCT BN2.B_name) AS total_businesses
        FROM BUSINESS_OWNER BO 
        LEFT JOIN MANAGES M2 ON BO.Phone_number = M2.Business_owner_id
        LEFT JOIN ASSOCIATED_STORES A2 ON BO.Phone_number = A2.Business_owner_id
        LEFT JOIN BUSINESS_NAME BN2 ON BO.Phone_number = BN2.Business_owner_id
        GROUP BY BO.Phone_number
    ) AS max_businesses
)
ORDER BY num_of_business DESC;

-- Query 7
SELECT City, COUNT(*) AS People_Visited
FROM JAPAN_TRIPS
GROUP BY City
ORDER BY People_Visited, City
LIMIT 5; 

-- Query 8
SELECT DISTINCT M.Username, M.Member_type 
FROM MEMBER M INNER JOIN COMMENT C ON M.Username = C.Member_id 
INNER JOIN PLAN P on M.Username = P.Member_id
WHERE (P.Start_date BETWEEN '2018-12-01' AND '2019-01-31')
OR C.Post_date BETWEEN '2018-12-01' AND '2019-01-31';

-- Query 9
SELECT P.Username, P.Minimum_Cost, P.Maximum_Cost, P.Average_Price
FROM PLAN_PRICES P INNER JOIN JAPAN_STATES_COUNT  J ON P.USERNAME = J.USERNAME
WHERE V_COUNT >= (SELECT COUNT(*) FROM JAPAN_STATES)
AND P.PLAN_ID IN (SELECT PLAN_ID
FROM JAPAN_TRIPS);

-- Query 10
SELECT  C.C_name AS Country_Name, Count(DISTINCT CM.Commenting_on) AS Comments, Count(DISTINCT M.C_name, M.Username) AS Members_from_Country, 
COUNT(DISTINCT A.Attraction_name, P.Plan_id) AS Related_Itineraries, COUNT(DISTINCT CV.Username, CV.Countries_Visited) AS Num_Memebers_Visited
FROM PLAN P LEFT JOIN ASSOCIATED_MEMBERS A_M ON P.Plan_id = A_M.Plan_id
          INNER JOIN ATTRACTIONS A ON P.Plan_id = A.Plan_id 
          INNER JOIN DESTINATION D ON A.Attraction_name = D.Dest_name
          RIGHT JOIN COUNTRY C ON D.C_name = C.C_name
          LEFT JOIN COMMENT CM ON D.Dest_name = CM.Commenting_on
		  LEFT JOIN MEMBER M ON M.C_name = C.C_name
          LEFT JOIN COUNTRIES_VISITED CV ON C.C_name = CV.Countries_Visited 
GROUP BY C.C_name;
























/*AUTHOR - NAVYA.S.RAJ
BATCH - S5 CSE
ROLL NO. - 51
SUBJECT - DBMS LAB*/

/*CREATING THE DATABASE*/
create database expt5;
use expt5;

create table book(
acc_no INT PRIMARY KEY,
title VARCHAR(50),
publisher VARCHAR(25),
year INT(4),
purch_date DATE,
status ENUM('issued','present in the library','reference','cannot be issued')
);

create table lib_member(
member_id INT PRIMARY KEY,
name VARCHAR(10),
no_of_books_issued INT,
max_limit INT
);

create table books_issue(
acc_no INT,
member_id INT,
issue_date DATE,
PRIMARY KEY(acc_no,member_id),
FOREIGN KEY(acc_no) REFERENCES book(acc_no),
FOREIGN KEY(member_id) REFERENCES lib_member(member_id)
);

insert into book values(2001,'Automata and Computability','Springer',1999,'2019-11-01','issued'),
(2002,'Automata and Computability','Springer',1999,'2019-11-01','issued'),
(2003,'Automata and Computability','Springer',1999,'2019-11-01','issued'),
(2004,'Automata and Computability','Springer',1999,'2019-11-01','issued'),
(2005,'Automata and Computability','Springer',1999,'2019-11-01','present in the library'),

(2006,'Computer Networks','Prentice Hall India',2011,'2020-05-17','issued'),
(2007,'Computer Networks','Prentice Hall India',2011,'2020-05-17','issued'),
(2008,'Computer Networks','Prentice Hall India',2011,'2020-05-17','issued'),
(2009,'Computer Networks','Prentice Hall India',2011,'2020-05-17','present in the library'),

(2010,'System Software','Pearson Education Asia',2004,'2019-09-23','issued'),
(2011,'System Software','Pearson Education Asia',2004,'2019-09-23','issued'),
(2012,'System Software','Pearson Education Asia',2004,'2019-09-23','present in the library'),

(2013,'Advanced Microprocessors and Peripherals','McGraw Hill',2013,'2022-01-01','issued'),
(2014,'Advanced Microprocessors and Peripherals','McGraw Hill',2013,'2022-01-01','present in the library');

insert into lib_member values(14101,'Navya',3,3),
(14102,'Nayana',2,3),
(14103,'Annie',3,3),
(14104,'Megha',1,3),
(14105,'Anjali',1,6);

insert into books_issue values(2001,14101,'2022-10-17'),
(2006,14101,'2022-10-17'),
(2010,14101,'2022-10-17'),

(2002,14102,'2022-10-01'),
(2011,14102,'2022-10-01'),

(2003,14103,'2022-10-23'),
(2007,14103,'2022-10-23'),
(2013,14103,'2022-10-23'),

(2004,14104,'2022-09-11'),

(2008,14105,'2022-10-29');

CREATE VIEW temp5 AS
SELECT *
FROM (book NATURAL JOIN lib_member) NATURAL JOIN books_issue;

SELECT *
FROM temp5;


/*Query 1*/
SELECT member_id,name,acc_no,title AS book_title,issue_date
FROM temp5 
WHERE CURDATE() >= DATE_ADD(issue_date,INTERVAL 15 DAY);


/*Query 2*/
SELECT DISTINCT member_id,name,no_of_books_issued
FROM temp5 
WHERE no_of_books_issued=max_limit;


/*Query 3*/
(SELECT /*acc_no,title,publisher,year,purch_date,*/title,count(*) as no_of_copies_issued
FROM temp5
WHERE status='issued'
GROUP BY title
ORDER BY no_of_copies_issued DESC
LIMIT 1					
)
UNION
(SELECT /*acc_no,title,publisher,year,purch_date,*/title,count(*) as no_of_copies_issued
FROM temp5
WHERE status='issued'
GROUP BY title
ORDER BY no_of_copies_issued ASC
LIMIT 1					
);


/**/
DROP table books_issue;
DROP table lib_member;
DROP table book;

DROP database expt5;

/*AUTHOR - NAVYA.S.RAJ
BATCH - S5 CSE
ROLL NO. - 51
SUBJECT - DBMS LAB*/

/*CREATING THE DATABASE*/
create database expt4;
use expt4;

/*CREATING THE TABLES - student,studentrank*/
create table student(
    rollno VARCHAR(10) primary key,
    name VARCHAR(20),
    category VARCHAR(10),
    district VARCHAR(10),
    state VARCHAR(10)
);

create table studentrank(
    rollno VARCHAR(10),
    mark INT,
    srank INT,
    FOREIGN KEY(rollno) REFERENCES student(rollno)
);

/*CREATING VIEW TABLE - temp4*/
CREATE VIEW temp4 AS
SELECT *
FROM student S NATURAL JOIN studentrank SR;

/*POPULATING THE DATABASE*/
insert into student values ('KTE2001','Abhijith','general','Kottayam','Kerala'),
('KTE2017','David','general','Kottayam','Kerala'),
('KTE2052','Diksha','OBC','Kottayam','Kerala'),
('KTE2075','Samarth','SC','Kottayam','Kerala'),

('DTU2023','Aman','general','Noida','Delhi'),
('DTU2034','Sampath','OBC','Noida','Delhi'),
('DTU2043','Amit','SC','Noida','Delhi'),
('DTU2060','Anushka','SC','Noida','Delhi'),

('DU2014','Aditi','general','CP','Delhi'),
('DU2061','Himanshi','general','CP','Delhi'),
('DU2028','Nagpal','SC','CP','Delhi');

insert into studentrank values('KTE2001',100,1),('KTE2017',85,2),('KTE2052',76,3),('KTE2075',60,4),
('DTU2023',86,3),('DTU2034',88,2),('DTU2043',99,1),('DTU2060',85,4),
('DU2014',100,1),('DU2061',99,2),('DU2028',83,3);


/*DISPLAYING THE TABLES*/
SELECT *
FROM student;

SELECT *
FROM studentrank;

SELECT *
FROM temp4;

/*PERFORMING QUERIES*/

/*Query 1 :List out the details of the students having same rank and same category*/
SELECT S1.*
FROM temp4 AS S1,temp4 AS S2
WHERE S1.category=S2.category AND S1.srank=S2.srank AND S1.rollno!=S2.rollno
ORDER BY S1.category,S1.srank;



/* Query 2: List out the details of the students (rollno, name, category, district, rank) who secured the highest
rank for each category in each state*/
SELECT T.rollno, T.name, T.category, T.district,T.state, T.srank
FROM temp4 as T
WHERE (T.category,T.state,T.srank) IN (SELECT T1.category,T1.state,MIN(T1.srank) as srank
      FROM temp4 as T1
      GROUP BY T1.state,T1.category);


/*Query 3: List the names of the students(roll no, name, category, district, mark, rank) having either marks
same but ranks different or marks different but ranks same together with the status (whether they
belong to the first category or second category)*/
SELECT S.rollno,S.name,S.category,S.district,S.state,S.mark,S.srank
FROM temp4 as S
WHERE S.mark IN (	SELECT S1.mark
			FROM temp4 as S1
			WHERE S1.mark=S.mark AND S.category = S1.category
			GROUP BY S1.mark
			HAVING count(*)>1 )
ORDER BY S.category ASC,S.mark DESC;


/*Query 4 : Find the category with the highest performance and the one with the least academic performance*/
SELECT S.category,avg(S.mark) as Avg_mark
FROM temp4 as S
GROUP BY category
HAVING avg(S.mark)>= ALL (	SELECT avg(mark)
				FROM temp4
				GROUP BY category)
UNION
(SELECT S.category,avg(S.mark) as Avg_mark
FROM temp4 as S
GROUP BY category
HAVING avg(S.mark)<= ALL (	SELECT avg(mark)
				FROM temp4
				GROUP BY category));				
SELECT avg(mark) AS Avg_mark
FROM temp4;


/*Query 5 : Find the category whose academic performance is below the average academic performance*/

/*Displaying the overall performance*/
SELECT avg(mark) AS Avg_mark
FROM temp4;

SELECT S.category,avg(mark) AS Avg_mark
FROM temp4 as S
GROUP BY S.category
HAVING avg(mark) < (	SELECT avg(mark)
			FROM temp4);


/*DROPPING THE TABLES AND DATABASE*/
DROP table studentrank;
DROP table student;

DROP database expt4;

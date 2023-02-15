CREATE TABLE student (name VARCHAR(50), roll_no int primary key, subject1 int, subject2 int, subject3 int, total_marks int, rank int);

DECLARE
  CURSOR cur_student IS
    SELECT name, roll_no, total_marks, RANK() OVER (ORDER BY total_marks DESC) AS rank
    FROM student;
    a_student cur_student%rowtype;
    v_rank NUMBER;
BEGIN

  -- Insert values into the student table RUN OK
  INSERT INTO student (name, roll_no, subject1, subject2, subject3, total_marks)
  VALUES ('Harikrishnan', 1, 90, 70, 70, 230);
  INSERT INTO student (name, roll_no, subject1, subject2, subject3, total_marks)
  VALUES ('Abhijith', 2, 95, 85, 70, 250);
  INSERT INTO student (name, roll_no, subject1, subject2, subject3, total_marks)
  VALUES ('John', 3, 80, 95, 85, 260);

  -- Open the cursor and loop through each record
  OPEN cur_student;
  LOOP
    FETCH cur_student INTO a_student;
    EXIT WHEN cur_student%NOTFOUND;

    -- Update the rank for each student
    UPDATE student
    SET rank = a_student.rank
    WHERE roll_no = a_student.roll_no;
  END LOOP;
  CLOSE cur_student;

  -- Commit the changes
  COMMIT;
  
END;
/

select * from student;
-- -- -- SQLite
SELECT *
from message_tb;
SELECT *
from chat_list_tb;


-- alter table message_tb rename to tmp;
-- CREATE TABLE message_tb
-- (
--     message_id BIGINT PRIMARY KEY,
--     user_name VARCHAR(16),
--     is_mine TINYINT,
--     timestamp BIGINT,
--     text TEXT,
--     is_send TINYINT
-- );
-- insert into message_tb
-- select*
-- from tmp;
-- drop TABLE tmp;
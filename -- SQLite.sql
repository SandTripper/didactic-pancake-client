-- SQLite
-- -- -- SQLite
-- alter table chat_list_tb add column is_show TINYINT DEFAULT 1;

-- UPDATE chat_list_tb SET unread_num  = 1;
SELECT *
from message_tb;
-- SELECT *
-- from chat_list_tb;

SELECT * FROM (SELECT * FROM message_tb WHERE user_name = 'FriendA') ORDER BY timestamp DESC limit 50 OFFSET 1

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
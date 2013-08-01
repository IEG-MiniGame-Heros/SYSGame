BEGIN TRANSACTION;
CREATE TABLE t_config (

  life_num     integer,

  reborn_cost  integer,

  map_size     integer,

  max_move_speed  integer,
  
  speed_increment  integer

);

CREATE TABLE t_frequency (

  id                integer,

  map_id            integer,

  type              integer,

  monster_min       integer,

  monster_max       integer,

  refresh_interval  integer

, refresh_num integer);

CREATE TABLE t_hero (

  id          integer,

  hero_name   varchar(50),

  skill_id    integer,

  move_speed  integer,

  hp          integer

, resource_path varchar(50), attack_range integer);

CREATE TABLE t_item (

  id             integer,

  item_name      varchar(50),

  duration       integer,

  exist_time     integer,

  describe       varchar(50),

  resource_path  varchar(50)

, value integer, item_type integer);

CREATE TABLE t_map (

  id             integer,

  map_name       varchar(50),

  need_kill_num  integer,

  resource_path  varchar(50)

);

CREATE TABLE t_monster (

  id             integer,

  monster_name   varchar(50),

  skill_id       integer,

  move_speed     integer,

  hp             integer,

  resource_path  varchar(50)

, attack_range integer);

CREATE TABLE t_reward (

  id          integer,

  monster_id  integer,

  item_id     integer,

  weight      integer

);

CREATE TABLE t_skill (

  id          integer,

  skill_name  integer,

  damage      integer,

  skill_cd    integer

, resource_path varchar(50));

CREATE TABLE t_user (

  id        integer,

  money     integer,

  kill_num  integer,

  username  varchar(50),

  password  varchar(50)

);

COMMIT;

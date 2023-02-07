REVOKE ALL PRIVILEGES ON * . * FROM 'trinity'@'%';

REVOKE ALL PRIVILEGES ON `world` . * FROM 'trinity'@'%';

REVOKE GRANT OPTION ON `world` . * FROM 'trinity'@'%';

REVOKE ALL PRIVILEGES ON `characters` . * FROM 'trinity'@'%';

REVOKE GRANT OPTION ON `characters` . * FROM 'trinity'@'%';

REVOKE ALL PRIVILEGES ON `auth` . * FROM 'trinity'@'%';

REVOKE GRANT OPTION ON `auth` . * FROM 'trinity'@'%';

DROP USER 'trinity'@'%';

DROP DATABASE IF EXISTS `world`;

DROP DATABASE IF EXISTS `characters`;

DROP DATABASE IF EXISTS `auth`;

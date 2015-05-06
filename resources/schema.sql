SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0;
SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0;
SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='TRADITIONAL';

DROP SCHEMA IF EXISTS `Media_Player` ;
CREATE SCHEMA IF NOT EXISTS `Media_Player` ;
USE `Media_Player` ;

-- -----------------------------------------------------
-- Table `Media_Player`.`Artist`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `Media_Player`.`Artist` ;

CREATE  TABLE IF NOT EXISTS `Media_Player`.`Artist` (
  `name` VARCHAR(45) NOT NULL ,
  `id` INT NOT NULL AUTO_INCREMENT ,
  PRIMARY KEY (`id`) ,
  UNIQUE INDEX `name_UNIQUE` (`name` ASC) )
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `Media_Player`.`Song`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `Media_Player`.`Song` ;

CREATE  TABLE IF NOT EXISTS `Media_Player`.`Song` (
  `Title` VARCHAR(100) NOT NULL ,
  `lyrics` LONGTEXT NULL ,
  `id` INT NOT NULL AUTO_INCREMENT ,
  `filePath` TEXT NULL ,
  `Artist_id` INT NOT NULL ,
  PRIMARY KEY (`id`) ,
  INDEX `fk_Song_Artist1` (`Artist_id` ASC) ,
  CONSTRAINT `fk_Song_Artist1`
    FOREIGN KEY (`Artist_id` )
    REFERENCES `Media_Player`.`Artist` (`id` )
    ON DELETE CASCADE
    ON UPDATE CASCADE)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `Media_Player`.`Album`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `Media_Player`.`Album` ;

CREATE  TABLE IF NOT EXISTS `Media_Player`.`Album` (
  `Title` VARCHAR(45) NOT NULL ,
  `AlbumCover` LONGBLOB NULL ,
  `id` INT NOT NULL AUTO_INCREMENT ,
  PRIMARY KEY (`id`) ,
  UNIQUE INDEX `id_UNIQUE` (`id` ASC) )
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `Media_Player`.`Playlist`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `Media_Player`.`Playlist` ;

CREATE  TABLE IF NOT EXISTS `Media_Player`.`Playlist` (
  `Name` VARCHAR(45) NOT NULL ,
  `id` INT NOT NULL AUTO_INCREMENT ,
  PRIMARY KEY (`id`) )
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `Media_Player`.`Song_has_Playlist`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `Media_Player`.`Song_has_Playlist` ;

CREATE  TABLE IF NOT EXISTS `Media_Player`.`Song_has_Playlist` (
  `Song_id` INT(11) NOT NULL ,
  `Playlist_id` INT NOT NULL ,
  PRIMARY KEY (`Song_id`, `Playlist_id`) ,
  INDEX `fk_Song_has_Playlist_Playlist1` (`Playlist_id` ASC) ,
  INDEX `fk_Song_has_Playlist_Song1` (`Song_id` ASC) ,
  CONSTRAINT `fk_Song_has_Playlist_Song1`
    FOREIGN KEY (`Song_id` )
    REFERENCES `Media_Player`.`Song` (`id` )
    ON DELETE CASCADE
    ON UPDATE CASCADE,
  CONSTRAINT `fk_Song_has_Playlist_Playlist1`
    FOREIGN KEY (`Playlist_id`)
    REFERENCES `Media_Player`.`Playlist` (`id`)
    ON DELETE CASCADE
    ON UPDATE CASCADE)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `Media_Player`.`Album_has_Artist`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `Media_Player`.`Album_has_Artist` ;

CREATE  TABLE IF NOT EXISTS `Media_Player`.`Album_has_Artist` (
  `Album_id` INT NOT NULL ,
  `Artist_id` INT NOT NULL ,
  PRIMARY KEY (`Album_id`, `Artist_id`) ,
  INDEX `fk_Album_has_Artist_Artist1` (`Artist_id` ASC) ,
  INDEX `fk_Album_has_Artist_Album1` (`Album_id` ASC) ,
  CONSTRAINT `fk_Album_has_Artist_Album1`
    FOREIGN KEY (`Album_id` )
    REFERENCES `Media_Player`.`Album` (`id` )
    ON DELETE CASCADE
    ON UPDATE CASCADE,
  CONSTRAINT `fk_Album_has_Artist_Artist1`
    FOREIGN KEY (`Artist_id` )
    REFERENCES `Media_Player`.`Artist` (`id` )
    ON DELETE CASCADE
    ON UPDATE CASCADE)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `Media_Player`.`Album_has_Song`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `Media_Player`.`Album_has_Song` ;

CREATE  TABLE IF NOT EXISTS `Media_Player`.`Album_has_Song` (
  `Album_id` INT NOT NULL ,
  `Song_id` INT NOT NULL ,
  PRIMARY KEY (`Album_id`, `Song_id`) ,
  INDEX `fk_Album_has_Song_Song1` (`Song_id` ASC) ,
  INDEX `fk_Album_has_Song_Album1` (`Album_id` ASC) ,
  CONSTRAINT `fk_Album_has_Song_Album1`
    FOREIGN KEY (`Album_id` )
    REFERENCES `Media_Player`.`Album` (`id` )
    ON DELETE CASCADE
    ON UPDATE CASCADE,
  CONSTRAINT `fk_Album_has_Song_Song1`
    FOREIGN KEY (`Song_id` )
    REFERENCES `Media_Player`.`Song` (`id` )
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `Media_Player`.`User`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `Media_Player`.`User` ;

CREATE  TABLE IF NOT EXISTS `Media_Player`.`User` (
  `id` INT NOT NULL AUTO_INCREMENT ,
  `username` VARCHAR(45) NOT NULL ,
  `password` VARCHAR(128) NULL ,
  `Fname` VARCHAR(20) NULL ,
  `Lname` VARCHAR(20) NULL ,
  UNIQUE INDEX `username_UNIQUE` (`username` ASC) ,
  PRIMARY KEY (`id`) )
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `Media_Player`.`User_has_Song`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `Media_Player`.`User_has_Song` ;

CREATE  TABLE IF NOT EXISTS `Media_Player`.`User_has_Song` (
  `User_id` INT NOT NULL ,
  `Song_id` INT NOT NULL ,
  `numberOfListens` INT NOT NULL DEFAULT 0 ,
  PRIMARY KEY (`User_id`, `Song_id`) ,
  INDEX `fk_User_has_Song_Song1` (`Song_id` ASC) ,
  INDEX `fk_User_has_Song_User1` (`User_id` ASC) ,
  CONSTRAINT `fk_User_has_Song_User1`
    FOREIGN KEY (`User_id` )
    REFERENCES `Media_Player`.`User` (`id` )
    ON DELETE CASCADE
    ON UPDATE CASCADE,
  CONSTRAINT `fk_User_has_Song_Song1`
    FOREIGN KEY (`Song_id` )
    REFERENCES `Media_Player`.`Song` (`id` )
    ON DELETE CASCADE
    ON UPDATE CASCADE)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Placeholder table for view `Media_Player`.`Favorite_Album`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `Media_Player`.`Favorite_Album` (`Album` INT, `Artist` INT, `Total Plays` INT);

-- -----------------------------------------------------
-- Placeholder table for view `Media_Player`.`Favorite_Artist`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `Media_Player`.`Favorite_Artist` (`Artist` INT, `Total Plays` INT);

-- -----------------------------------------------------
-- Placeholder table for view `Media_Player`.`Favorite_Song`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `Media_Player`.`Favorite_Song` (`Artist` INT, `Album` INT, `Title` INT, `Total Plays` INT);

-- -----------------------------------------------------
-- View `Media_Player`.`Favorite_Album`
-- -----------------------------------------------------
DROP VIEW IF EXISTS `Media_Player`.`Favorite_Album` ;
DROP TABLE IF EXISTS `Media_Player`.`Favorite_Album`;
USE `Media_Player`;
CREATE  OR REPLACE VIEW `Media_Player`.`Favorite_Album` AS
select `Al`.`Title` AS `Album`, `Ar`.`name` AS `Artist`, SUM(`S`.`numberOfListens`) AS `Total Plays`
FROM `Artist` Ar, `Album` Al, `Song` S
WHERE `S`.`Album_id`=`Al`.`id` AND `Al`.`Artist_id`=`Ar`.`id`
GROUP BY `Album`
ORDER BY `Total Plays` DESC
LIMIT 1;

-- -----------------------------------------------------
-- View `Media_Player`.`Favorite_Artist`
-- -----------------------------------------------------
DROP VIEW IF EXISTS `Media_Player`.`Favorite_Artist` ;
DROP TABLE IF EXISTS `Media_Player`.`Favorite_Artist`;
USE `Media_Player`;
CREATE  OR REPLACE VIEW `Media_Player`.`Favorite_Artist` AS
SELECT `Ar`.`name` AS `Artist`, SUM(`S`.`numberOfListens`) AS `Total Plays`
FROM `Song` S
JOIN `Album` Al
ON `S`.Album_id=`Al`.`id`
JOIN `Artist` Ar
ON `Al`.`Artist_id`=`Ar`.`id`
GROUP BY `Artist`
ORDER BY `Total Plays` DESC
LIMIT 1;

-- -----------------------------------------------------
-- View `Media_Player`.`Favorite_Song`
-- -----------------------------------------------------
DROP VIEW IF EXISTS `Media_Player`.`Favorite_Song` ;
DROP TABLE IF EXISTS `Media_Player`.`Favorite_Song`;
USE `Media_Player`;
CREATE  OR REPLACE VIEW `Media_Player`.`Favorite_Song` AS
SELECT `Ar`.`name` AS `Artist`, `Al`.`Title` AS `Album`, 
        `S`.`Title`, `S`.`numberOfListens` AS `Total Plays`
FROM `Song` S
JOIN `Album` Al
ON `S`.`Album_id`=`Al`.`id`
JOIN `Artist` Ar
ON `Al`.`Artist_id`=`Ar`.`id`
ORDER BY `Total Plays` DESC
LIMIT 1;


SET SQL_MODE=@OLD_SQL_MODE;
SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS;
SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS;

SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0;
SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0;
SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='TRADITIONAL,ALLOW_INVALID_DATES';

DROP SCHEMA IF EXISTS `Media_Player` ;
CREATE SCHEMA IF NOT EXISTS `Media_Player` ;
USE `Media_Player` ;

-- -----------------------------------------------------
-- Table `Media_Player`.`Artist`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `Media_Player`.`Artist` ;

CREATE TABLE IF NOT EXISTS `Media_Player`.`Artist` (
  `name` VARCHAR(45) NOT NULL,
  PRIMARY KEY (`name`),
  UNIQUE INDEX `name_UNIQUE` (`name` ASC))
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `Media_Player`.`Album`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `Media_Player`.`Album` ;

CREATE TABLE IF NOT EXISTS `Media_Player`.`Album` (
  `Title` VARCHAR(45) NOT NULL,
  `AlbumCover` LONGBLOB NULL,
  `Artist_name` VARCHAR(45) NOT NULL,
  PRIMARY KEY (`Title`, `Artist_name`),
  INDEX `fk_Album_Artist_idx` (`Artist_name` ASC),
  CONSTRAINT `fk_Album_Artist`
    FOREIGN KEY (`Artist_name`)
    REFERENCES `Media_Player`.`Artist` (`name`)
    ON DELETE CASCADE
    ON UPDATE CASCADE)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `Media_Player`.`Song`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `Media_Player`.`Song` ;

CREATE TABLE IF NOT EXISTS `Media_Player`.`Song` (
  `Title` VARCHAR(100) NOT NULL,
  `numberOfListens` INT NOT NULL DEFAULT 0,
  `lyrics` LONGTEXT NULL,
  `Album_Title` VARCHAR(45) NOT NULL,
  `Album_Artist_name` VARCHAR(45) NOT NULL,
  `id` VARCHAR(45) NOT NULL,
  `filePath` TEXT NULL,
  PRIMARY KEY (`Album_Title`, `Album_Artist_name`, `id`),
  INDEX `fk_Song_Album1_idx` (`Album_Title` ASC, `Album_Artist_name` ASC),
  UNIQUE INDEX `id_UNIQUE` (`id` ASC),
  CONSTRAINT `fk_Song_Album1`
    FOREIGN KEY (`Album_Title` , `Album_Artist_name`)
    REFERENCES `Media_Player`.`Album` (`Title` , `Artist_name`)
    ON DELETE CASCADE
    ON UPDATE CASCADE)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `Media_Player`.`Playlist`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `Media_Player`.`Playlist` ;

CREATE TABLE IF NOT EXISTS `Media_Player`.`Playlist` (
  `Name` VARCHAR(45) NOT NULL,
  PRIMARY KEY (`Name`))
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `Media_Player`.`Playlist_has_Song`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `Media_Player`.`Playlist_has_Song` ;

CREATE TABLE IF NOT EXISTS `Media_Player`.`Playlist_has_Song` (
  `Playlist_Name` VARCHAR(45) NOT NULL,
  `Song_Album_Title` VARCHAR(45) NOT NULL,
  `Song_Album_Artist_name` VARCHAR(45) NOT NULL,
  `Song_id` VARCHAR(45) NOT NULL,
  PRIMARY KEY (`Playlist_Name`, `Song_Album_Title`, `Song_Album_Artist_name`, `Song_id`),
  INDEX `fk_Playlist_has_Song_Song1_idx` (`Song_Album_Title` ASC, `Song_Album_Artist_name` ASC, `Song_id` ASC),
  INDEX `fk_Playlist_has_Song_Playlist1_idx` (`Playlist_Name` ASC),
  CONSTRAINT `fk_Playlist_has_Song_Playlist1`
    FOREIGN KEY (`Playlist_Name`)
    REFERENCES `Media_Player`.`Playlist` (`Name`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_Playlist_has_Song_Song1`
    FOREIGN KEY (`Song_Album_Title` , `Song_Album_Artist_name` , `Song_id`)
    REFERENCES `Media_Player`.`Song` (`Album_Title` , `Album_Artist_name` , `id`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;

USE `Media_Player` ;

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
CREATE TABLE IF NOT EXISTS `Media_Player`.`Favorite_Song` (`Title` INT, `Total Plays` INT);

-- -----------------------------------------------------
-- View `Media_Player`.`Favorite_Album`
-- -----------------------------------------------------
DROP VIEW IF EXISTS `Media_Player`.`Favorite_Album` ;
DROP TABLE IF EXISTS `Media_Player`.`Favorite_Album`;
USE `Media_Player`;
CREATE  OR REPLACE VIEW `Media_Player`.`Favorite_Album` AS
select Album_Title AS `Album`, Album_Artist_name AS `Artist`, SUM(numberOfListens) AS `Total Plays`
FROM Song 
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
SELECT Album_Artist_name AS `Artist`, SUM(numberOfListens) AS `Total Plays`
FROM Song
GROUP BY Artist
ORDER BY `Total Plays` DESC
LIMIT 1;

-- -----------------------------------------------------
-- View `Media_Player`.`Favorite_Song`
-- -----------------------------------------------------
DROP VIEW IF EXISTS `Media_Player`.`Favorite_Song` ;
DROP TABLE IF EXISTS `Media_Player`.`Favorite_Song`;
USE `Media_Player`;
CREATE  OR REPLACE VIEW `Media_Player`.`Favorite_Song` AS
SELECT Title, numberOfListens AS `Total Plays`
FROM Song
ORDER BY `Total Plays` DESC
LIMIT 1;

SET SQL_MODE=@OLD_SQL_MODE;
SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS;
SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS;

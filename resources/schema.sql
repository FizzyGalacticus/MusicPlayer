SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0;
SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0;
SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='TRADITIONAL';

DROP SCHEMA IF EXISTS `Media_Player` ;
CREATE SCHEMA IF NOT EXISTS `Media_Player` DEFAULT CHARACTER SET latin1 COLLATE latin1_swedish_ci ;
USE `Media_Player` ;

-- -----------------------------------------------------
-- Table `Media_Player`.`Artist`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `Media_Player`.`Artist` ;

CREATE  TABLE IF NOT EXISTS `Media_Player`.`Artist` (
  `name` VARCHAR(45) NOT NULL ,
  `id` INT(11) NOT NULL AUTO_INCREMENT ,
  PRIMARY KEY (`id`) ,
  UNIQUE INDEX `name_UNIQUE` (`name` ASC) )
ENGINE = InnoDB
AUTO_INCREMENT = 4
DEFAULT CHARACTER SET = latin1
COLLATE = latin1_swedish_ci;


-- -----------------------------------------------------
-- Table `Media_Player`.`Song`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `Media_Player`.`Song` ;

CREATE  TABLE IF NOT EXISTS `Media_Player`.`Song` (
  `Title` VARCHAR(100) NOT NULL ,
  `lyrics` LONGTEXT NULL DEFAULT NULL ,
  `id` INT(11) NOT NULL AUTO_INCREMENT ,
  `filePath` TEXT NULL DEFAULT NULL ,
  `Artist_id` INT(11) NOT NULL ,
  PRIMARY KEY (`id`) ,
  UNIQUE INDEX `subkey_UNIQUE` (`Title` ASC, `Artist_id` ASC) ,
  INDEX `fk_Song_Artist1` (`Artist_id` ASC) ,
  CONSTRAINT `fk_Song_Artist1`
    FOREIGN KEY (`Artist_id` )
    REFERENCES `Media_Player`.`Artist` (`id` )
    ON DELETE CASCADE
    ON UPDATE CASCADE)
ENGINE = InnoDB
AUTO_INCREMENT = 872
DEFAULT CHARACTER SET = latin1
COLLATE = latin1_swedish_ci;


-- -----------------------------------------------------
-- Table `Media_Player`.`Album`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `Media_Player`.`Album` ;

CREATE  TABLE IF NOT EXISTS `Media_Player`.`Album` (
  `Title` VARCHAR(45) NOT NULL ,
  `AlbumCover` LONGBLOB NULL DEFAULT NULL ,
  `id` INT(11) NOT NULL AUTO_INCREMENT ,
  `Artist_id` INT(11) NOT NULL ,
  PRIMARY KEY (`id`) ,
  UNIQUE INDEX `id_UNIQUE` (`id` ASC) ,
  UNIQUE INDEX `subkey_UNIQUE` (`Title` ASC, `Artist_id` ASC) ,
  INDEX `fk_Album_Artist1` (`Artist_id` ASC) ,
  CONSTRAINT `fk_Album_Artist1`
    FOREIGN KEY (`Artist_id` )
    REFERENCES `Media_Player`.`Artist` (`id` )
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB
AUTO_INCREMENT = 886
DEFAULT CHARACTER SET = latin1
COLLATE = latin1_swedish_ci;


-- -----------------------------------------------------
-- Table `Media_Player`.`Playlist`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `Media_Player`.`Playlist` ;

CREATE  TABLE IF NOT EXISTS `Media_Player`.`Playlist` (
  `Name` VARCHAR(45) NOT NULL ,
  `id` INT(11) NOT NULL AUTO_INCREMENT ,
  PRIMARY KEY (`id`) )
ENGINE = InnoDB
DEFAULT CHARACTER SET = latin1
COLLATE = latin1_swedish_ci;


-- -----------------------------------------------------
-- Table `Media_Player`.`Song_has_Playlist`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `Media_Player`.`Song_has_Playlist` ;

CREATE  TABLE IF NOT EXISTS `Media_Player`.`Song_has_Playlist` (
  `Song_id` INT(11) NOT NULL ,
  `Playlist_id` INT(11) NOT NULL ,
  PRIMARY KEY (`Song_id`, `Playlist_id`) ,
  INDEX `fk_Song_has_Playlist_Playlist1` (`Playlist_id` ASC) ,
  INDEX `fk_Song_has_Playlist_Song1` (`Song_id` ASC) ,
  CONSTRAINT `fk_Song_has_Playlist_Song1`
    FOREIGN KEY (`Song_id` )
    REFERENCES `Media_Player`.`Song` (`id` )
    ON DELETE CASCADE
    ON UPDATE CASCADE,
  CONSTRAINT `fk_Song_has_Playlist_Playlist1`
    FOREIGN KEY (`Playlist_id` )
    REFERENCES `Media_Player`.`Playlist` (`id` )
    ON DELETE CASCADE
    ON UPDATE CASCADE)
ENGINE = InnoDB
DEFAULT CHARACTER SET = latin1
COLLATE = latin1_swedish_ci;


-- -----------------------------------------------------
-- Table `Media_Player`.`Album_has_Song`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `Media_Player`.`Album_has_Song` ;

CREATE  TABLE IF NOT EXISTS `Media_Player`.`Album_has_Song` (
  `Album_id` INT(11) NOT NULL ,
  `Song_id` INT(11) NOT NULL ,
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
ENGINE = InnoDB
DEFAULT CHARACTER SET = latin1
COLLATE = latin1_swedish_ci;


-- -----------------------------------------------------
-- Table `Media_Player`.`User`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `Media_Player`.`User` ;

CREATE  TABLE IF NOT EXISTS `Media_Player`.`User` (
  `id` INT(11) NOT NULL AUTO_INCREMENT ,
  `username` VARCHAR(45) NOT NULL ,
  `password` BLOB NOT NULL ,
  `Fname` VARCHAR(20) NULL DEFAULT NULL ,
  `Lname` VARCHAR(20) NULL DEFAULT NULL ,
  `email` VARCHAR(100) NULL DEFAULT NULL ,
  `joinDateTime` DATETIME NOT NULL ,
  PRIMARY KEY (`id`) ,
  UNIQUE INDEX `username_UNIQUE` (`username` ASC) )
ENGINE = InnoDB
AUTO_INCREMENT = 4
DEFAULT CHARACTER SET = latin1
COLLATE = latin1_swedish_ci;


-- -----------------------------------------------------
-- Table `Media_Player`.`User_has_Song`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `Media_Player`.`User_has_Song` ;

CREATE  TABLE IF NOT EXISTS `Media_Player`.`User_has_Song` (
  `User_id` INT(11) NOT NULL ,
  `Song_id` INT(11) NOT NULL ,
  `numberOfListens` INT(11) NOT NULL DEFAULT '0' ,
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
ENGINE = InnoDB
DEFAULT CHARACTER SET = latin1
COLLATE = latin1_swedish_ci;



SET SQL_MODE=@OLD_SQL_MODE;
SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS;
SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS;

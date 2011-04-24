/* 
 Boxer is copyright 2011 Alun Bestor and contributors.
 Boxer is released under the GNU General Public License 2.0. A full copy of this license can be
 found in this XCode project at Resources/English.lproj/BoxerHelp/pages/legalese.html, or read
 online at [http://www.gnu.org/licenses/gpl-2.0.txt].
 */


#import "BXOperation.h"


@class BXDrive;

@protocol BXDriveImport <NSObject>

//The drive to import.
@property (retain) BXDrive *drive;

//The base folder into which to import the drive to.
//This does not include the destination drive name, which will be determined automatically
//from the drive being imported.
@property (copy) NSString *destinationFolder;

//The path of the new drive once it is finally imported.
@property (copy, readonly) NSString *importedDrivePath;

//Whether the source files will be left behind after importing.
@property (assign) BOOL copyFiles;

//The number of bytes that will be copied in total, and have been copied so far.
@property (readonly) unsigned long long numBytes;
@property (readonly) unsigned long long bytesTransferred;


//Returns whether this import class is appropriate for importing the specified drive.
+ (BOOL) isSuitableForDrive: (BXDrive *)drive;

//Returns the name under which the specified drive would be saved.
+ (NSString *) nameForDrive: (BXDrive *)drive;

//Return a suitably initialized BXOperation subclass for transferring the drive.
- (id <BXDriveImport>) initForDrive: (BXDrive *)drive
					  toDestination: (NSString *)destinationFolder
						  copyFiles: (BOOL)copyFiles;


//Undo the import operation. Called automatically if the operation is cancelled
//or encounters an unrecoverable error.
//Returns YES if the import was undone, NO if there was nothing to undo
//(e.g. the operation hadn't successfully imported anything.)
- (BOOL) undoTransfer;

@end


@interface BXDriveImport: BXOperation

+ (id <BXDriveImport>) importOperationForDrive: (BXDrive *)drive
						toDestination: (NSString *)destinationFolder
							copyFiles: (BOOL)copyFiles;

//Returns the most suitable operation class to import the specified drive
+ (Class) importClassForDrive: (BXDrive *)drive;

//Returns a safe replacement import operation for the specified failed import,
//or nil if no fallback was available.
//The replacement will have the same source drive and destination folder as
//the original import.
//Used when e.g. a disc-ripping import fails because of a driver-related issue:
//this will fall back on a safer method of importing.
+ (id <BXDriveImport>) fallbackForFailedImport: (id <BXDriveImport>)failedImport;

@end

//A protocol for import-related error subclasses.
@protocol BXDriveImportError

+ (id) errorWithDrive: (BXDrive *)drive;

@end
/* 
 Boxer is copyright 2011 Alun Bestor and contributors.
 Boxer is released under the GNU General Public License 2.0. A full copy of this license can be
 found in this XCode project at Resources/English.lproj/BoxerHelp/pages/legalese.html, or read
 online at [http://www.gnu.org/licenses/gpl-2.0.txt].
 */

//BXDriveBundleImport wraps BIN/CUE images and any associated audio tracks into a .cdmedia bundle,
//rewriting cue paths as necessary.

#import "BXMultiFileTransfer.h"
#import "BXDriveImport.h"

@interface BXDriveBundleImport : BXMultiFileTransfer <BXDriveImport>
{
	@private
	BXDrive *_drive;
	NSString *_destinationFolder;
	NSString *_importedDrivePath;
}
@end

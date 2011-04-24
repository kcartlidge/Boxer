/* 
 Boxer is copyright 2011 Alun Bestor and contributors.
 Boxer is released under the GNU General Public License 2.0. A full copy of this license can be
 found in this XCode project at Resources/English.lproj/BoxerHelp/pages/legalese.html, or read
 online at [http://www.gnu.org/licenses/gpl-2.0.txt].
 */

#import "BXShelfArt.h"

@implementation BXShelfArt
@synthesize sourceImage;

- (id) initWithSourceImage: (NSImage *)image
{
	if ((self = [super init]))
	{
		[self setSourceImage: image];
	}
	return self;
}

- (void) dealloc
{
	[self setSourceImage: nil], [sourceImage release];
	[super dealloc];
}

- (void) drawInRect: (NSRect)frame
{
	NSAssert([self sourceImage] != nil, @"[BXShelfArt -drawInRect:] called before source image was set.");
	
	NSColor *tileColor = [NSColor colorWithPatternImage: [self sourceImage]];
	NSSize tileSize = [[self sourceImage] size];
	
	//Set the phase so that the art is drawn from the top left corner of the frame
	NSUInteger offset = (NSUInteger)frame.size.height % (NSUInteger)tileSize.height;
	
	NSPoint tilePhase = NSMakePoint(frame.origin.x,
									frame.origin.y + (CGFloat)offset);
	
	//Combine with the phase of the inherited graphics context
	NSPoint initialPhase = [[NSGraphicsContext currentContext] patternPhase];
	NSPoint combinedPhase = NSMakePoint(tilePhase.x + initialPhase.x,
										tilePhase.y + initialPhase.y);
	
	[NSGraphicsContext saveGraphicsState];
		[[NSGraphicsContext currentContext] setPatternPhase: combinedPhase];
		[tileColor set];
		NSRectFill(frame);
	[NSGraphicsContext restoreGraphicsState];
}

//Returns a new NSImage containing the source image tiled to fill the specified size.
- (NSImage *)tiledImageWithSize: (NSSize)size
{
	NSAssert([self sourceImage] != nil, @"[BXShelfArt -tiledImageWithSize:] called before source image was set.");
	
	NSImage *image = [[NSImage alloc] initWithSize: size];
	NSRect frame = NSMakeRect(0, 0, size.width, size.height);
	
	[image lockFocus];
		[self drawInRect: frame];
	[image unlockFocus];
	
	return [image autorelease];
}
@end

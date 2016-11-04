/**
 *  @file
 *  @brief 
 *  @author wplaat
 *
 *  Copyright (C) 2008-2016 PlaatSoft
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, version 3.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

package nl.plaatsoft.redsquare.resources;

import java.io.ByteArrayInputStream;
import java.util.Base64;

import javafx.scene.image.Image;

public class Squares {
	
	public static Image getBlue1() {
		
		String image = 
		"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";
	
		return new Image(new ByteArrayInputStream(Base64.getDecoder().decode(image)));
	}

	
	public static Image getBlue2() {
		
		String image = 				
		"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";
	
		return new Image(new ByteArrayInputStream(Base64.getDecoder().decode(image)));
	}

	
	public static Image getBlue3() {
		
		String image = 		
		"iVBORw0KGgoAAAANSUhEUgAAAEAAAAB4CAYAAABCQPQeAAAAAXNSR0IArs4c6QAAAAZiS0dEAP8A/wD/oL2nkwAAAAlwSFlzAAALEwAACxMBAJqcGAAAAAd0"+
		"SU1FB9gMARMAIGr7g2cAAATCSURBVHja7ZhdkuM2DISb0M9srpWD5B45Qc6Ri+y1MjsWgTywCcGzM1nZ+5TaVpVLEk1bwsdGEySg49c+GgDg9/gTAUOg8WNY"+
		"YKXN0NDQsPA3ox0wAIbGe7vrP64bDA1g/6tvFQgAAee1o/HaSxv4aQheBwIdgcj+DY5efj/bvra/wAB+6eOXB7B+17Lhb/wDYKNkOxolPK4B4IXnVwrwSxEi"+
		"KPdg2w7g7Yk3m78z/utMi5mArzx/Yf9v7DcSdxwL294Q+A3AgT9+DODAjg3ADQ1bycCNLjD6jCB3NHQEbsysje1WsrnRDR53p5YuVL3hxvOGwIKGG3EvqenA"+
		"LX83vt8QOK4qoGPHxiC8BNHLiAYavuUrDTgHLW88FFj5Hye2x+15Bn8gsPFphsDK53UEDgRe+N0bbbBRh47ICG8F0n8CWLDjlQHMUX/jfeOIOwwvAG4AFhic"+
		"KVMD7/T/gSWemAWm+iLnnAmiU+Ydjhcq0uB8wwFmT8UMSPtVBQQ2rGhYc+IAp7eAUdydjxojDyxo6RVHjvgA0PPusaNTARPFwYB6nk8YnZCM425onC6BlRPq"+
		"J0OwfkD/JaUNfixzu/FX46rz+wMNS/59Pbfy2EcQnMaH/JztB6F0nlcqAKmOs3+U6uaSAgw7DgAOw8rcbzB0vtKasm6Z8wv7zVH3Erw9WAS9L4ZmEMZ0CAbs"+
		"GVRVyZn3QwkDVsCxpKf9MAX2rN96GUFjNXgU6c9KrycKo3lZGueS0+hjHgAGuaSxeUp8psGsCreiCkvnONUwwV1SgGODMYSjeIDT8IJqCDQsvDYYDgA7z5al"+	
		"M9Ka8GACnNKdBa5jBfDGs3NUOzxNscFxEJRzvJcsqv2aBxh21gCWM3pkEJYV9ZR64/1KJcx/6T+RBo2Vfs1zcOTXrEzOGcKzFhhKqfAcjhsc28ca+EgBO5c1"+
		"QwGWQQ9fsBTaBLOkOSIXPlbKoWqoVxVwb1wjn2dV4gwsOCeco++5SALBOKE8oADHnqu6xsfGu9WeZ8YbFTDrLkv3P9cZ9pQCOt8Geb6XsmW447zwLTr7zn4D"+
		"XmTKXEqB03Isi5mebUPuXpbO0wLPJfCZLlZmiEdcYI7yRI5SGiFtzrNcniBmW6PxjXb/rBz/vA4AA/MMclrKmd+t7AtEeoJx9Mf0OL37UQDDZD13BkY2n/mN"+
		"si/QMyEdjRpoDLruDVyuBEcNYMXsLCvxVu6N/FtRynz09ICf3RCJOw+IMrrOvJ/tnsHe34+0sKseAJpgZH63tBnDwmBPIN/vEJ07RZFKek4BZ+572fE5LTkY"+
		"KDJw51wRZTfp/O5yHTAD8HcSn+upKCYZpV97t1U2oT1TCltOfDPYE4CXLbF7IECwfPOyJRb8XDTBVoyszuXtzuxOn7C8t7tRP/cYn1kORXmburLwUinWdpQk"+
		"jbIMb3dle2hLTAAEQAAEQAAEQAAEQAAEQAAEQAAEQAAEQAAEQAAEQAAEQAAEQAAEQAAEQAAEQAAEQAAEQAAEQAAEQAAEQAAEQAAEQAAEQAAEQAAEQAAEQAAE"+
		"QAAEQAAEQAAEQAAEQAAEQAAEQAAEQAAEQAAEQAAEQAAEQAAEQAAEQAAEQAAEQAAEQAAEQAAEQAAEQAAEQMf/7vgXZWCQsANxrZwAAAAASUVORK5CYII=";
		
		return new Image(new ByteArrayInputStream(Base64.getDecoder().decode(image)));
	}
	
	
	public static Image getBlue4() {
		
		String image = 	
		"iVBORw0KGgoAAAANSUhEUgAAAEAAAABACAYAAACqaXHeAAAAAXNSR0IArs4c6QAAAAZiS0dEAP8A/wD/oL2nkwAAAAlwSFlzAAALEwAACxMBAJqcGAAAAAd0"+
		"SU1FB9gMARMAO+CeSosAAARlSURBVHja7Zhdlts2DIUvoB+n2+pCuo+uoOvoRrKtTmwR6AMvQXgySSTncaBzfCTRtCV8vLgECdTxuQ+Jqz/9bzgUDuFHsUBT"+
		"m0IgECz8XW8HFIBCeK9P/fu1QCEA+599M4cDcBivDcJrS23gR+C8djgaHB79BYaWfj/avso/+tkV8OkBrB+2bvgX/wHYKNkGoYT7NQDceH6jAL8kIYJyd7bt"+
		"AO4vvN34nfJfR1qMBHzj+Qv7f2O/nrj9WNh2h+MPAAf++jWAAzs2AA8ItpSBG12g9+lB7hA0OB7MrI3tmrJZ6AbXHUrChbI3PHje4FggeBD3Erp2POJ3/fsN"+
		"juOsAhp2bAzCUhAtjahD8C1eqcM5aHn9ocDK/5jYrlv0CP6AY+PTFI6Vz2twHHDc+N2dNijUocEjykeC9FMAC3a8MYAx6nfeC0fcoLgBeABYoDCmTA680f87"+
		"Fn9hFhjq85hzBohGmTcYblSkwviGHcweiumQ9rMKcGxYIVhj4gCnN4dS3I2P6iMPLJDwiiNGvANocXftaFTAQHEwoBbnCaMRknLcFcLpElg5oX4wBOsP6N9C"+
		"2uBHI7eFv+xXjd8fECzx9/ks6bFXEEzjQ3xm+0EojeeVCkCoY/b3VN2cUoBixwHAoFiZ+wJF4yutIWuJnF/Yb4y6peD1YhH0vhgaQSjTwRmwRVBZJTPvuxI6"+
		"LIdhCU/7ZQrsUb+1NILKavBI0h+VXgsUSvPSMM4lptFrHgAGuYSxWUh8pMGoCrekCg3nmGoY4E4pwLBBGcKRPMBoeE41OAQLrxWKA8DOs0bpjLAmXEyAKd1R"+
		"4BpWAHeejaPaYGGKAsNBUMbxXqKotnMeoNhZA2jM6B5BaFTUQ+rC+5VKGP/SfiMNhJV+znNw5NeoTOYMYVELdKVkeAbDA4btew38SAE7lzVdARpBd1/QENoA"+
		"s4Q5IhY+msqhbKhnFfBsXD2fR1ViDMw5J8zRt1gkgWCMUC4owLDHqk74WH+32rPIeKUCRt2l4f5zraEvKaDxbRDnZylrhNvPC9+ise/o1+F5pMypFJiWo1HM"+
		"tGjrcre0dB4WOJfAM100zRBXXGCM8kCOVBohbM6iXB4gRpvQ+Hq7fVSO/7wOAAOzCHJYysxvSfsCHp6gHP0+PQ7vvgqgm6zFzkDP5pnfSPsCLRLSINSAMOi8"+
		"N3C6Euw1gCaz06jEJd0r+UtSynj08IDf3RDxJw/wNLrGvB/tFsE+3/e00LMeAJqgR35L2IxiYbATyPc7RHOnyENJrylg5r6lHZ9pyc5AEYEb5wpPu0nzu9N1"+
		"wAjA3kl8rKc8maSnfvJuq2xAe6UU1pj4RrATgKUtsWcggLN8s7Ql5vycNEFJRpbncnkyu+kTGvf6NOpzj/GV5ZCnt8krC0uVYm5HSlJPy3B5Ktu9tsQKQAEo"+
		"AAWgABSAAlAACkABKAAFoAAUgAJQAApAASgABaAAFIACUAAKQAEoAAWgABSAAlAACkABKAAFoAAUgDo+xfE/x7+QQFGhXnQAAAAASUVORK5CYII=";
		
		return new Image(new ByteArrayInputStream(Base64.getDecoder().decode(image)));
	}
	
	public static Image getRed() {
		
		String image = 				
		"iVBORw0KGgoAAAANSUhEUgAAAEAAAABACAYAAACqaXHeAAAAAXNSR0IArs4c6QAAAAZiS0dEAP8A/wD/oL2nkwAAAAlwSFlzAAALEwAACxMBAJqcGAAAAAd0"+
		"SU1FB9gMARMBJ+2EJ4UAAAH0SURBVHja7ZjdbcMwDISPRtINO0an6RYdUuyLCxgHUtSP89KcAIG2ZSfmp6MsEnjzZgDgwNd5fCTWOuPXzmO4WJt4Lz9tu1gn"+
		"e+0eWE+uNwBuwPf15d62vT2AR3DthyRrFDJOYzyO5HwlBPg4GvPLsSXP/tnPEQDPxEGn88i5DMxu88CZzFGnd/YEZArgg5yoZrxSg206Xs36iCJ8JgSehZPR"+
		"TGdgfBFE5YRTR2J7oVQqoDfj1pl9e6ECvKMCLxSBGQBGMR/NOAoYFqwbK3FvyWz3rvG5zSjgseB4BgI3hACK2Z4BMbwGHAMAkOwWKxCrAKLeintB906FgNFG"+
		"yQb7kUDb+fw5bYl9UA38zJQCkDiETo6ARD13KaBdzqM9PxJgWFVAJHVQolMlP3ckQ73kqAX3tjvWACRyPhLZH6SA4/zTnXyjnb/VaJZbEg4tCRvsrgHWcZqh"+
		"9ODtxD7HM6sgWweW1gB2EAP1AQ4LVsBqCBjl/kjqANmXodG1YQARhKMojFihhN2CiAdORRaJOpZCoKoIReFwvABAS2Q/WhGa2gn+15LYEAC7se8mRTNZqBVF"+
		"mTAfUE1QAARAAARAAARAAARAAARAAARAAARAAARAAARAAARAAARAAARAAARAAARAAARAAARAAARAAARAAARATe2/tl/xWC0gcvo7+wAAAABJRU5ErkJggg==";
		
		return new Image(new ByteArrayInputStream(Base64.getDecoder().decode(image)));
	}
	
}

global func ComDirTransform(int comdir, int tocomdir)
{
	if (comdir == tocomdir) return comdir;
	if (comdir == COMD_Stop) return tocomdir;
	if (comdir == (tocomdir + 3) % 8 + 1) return COMD_Stop;
	if (Inside(comdir, tocomdir + 1, tocomdir + 3)) return comdir - 1;
	if (Inside(comdir, tocomdir - 1, tocomdir - 3)) return comdir + 1;
	if (Inside(comdir, tocomdir - 7, tocomdir - 5)) return (comdir + 6) % 8 + 1;
	return comdir % 8 + 1;
}

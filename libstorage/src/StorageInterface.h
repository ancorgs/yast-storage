#ifndef STORAGEINTERFACE_H
#define STORAGEINTERFACE_H


#include <string>
#include <list>

using std::string;
using std::list;


namespace storage
{
    enum FsType { UNKNOWN, REISERFS, EXT2, EXT3, VFAT, XFS, JFS, NTFS, SWAP };

    enum PartitionType { PRIMARY, EXTENDED, LOGICAL };

    enum MdType { RAID0, RAID1, RAID5, MULTIPATH };


    /**
     * Contains capabilities of a filesystem type.
     */
    struct FsCapabilities
    {
	bool isExtendable;
	bool isExtendableWhileMounted;
	bool isReduceable;
	bool isReduceableWhileMounted;
	bool supportsUuid;
	bool supportsLabel;
	bool labelWhileMounted;
	int labelLength;
    };


    /**
     * Contains info about a partition.
     */
    struct PartitionInfo
    {
	string name;
	unsigned long cyl_start;
	unsigned long cyl_size;
	FsType fstype;
    };

    /**
     * prelimiary list of error codes, must have negative values
     */
    enum ErrorCodes
    {
	DISK_CREATED_PARTITION_OVERLAPS_EXISTING = -1000,
	DISK_CREATED_PARTITION_EXCEEDS_DISK = -1001
    };


    /**
     * \brief Abstract class defining the interface for libstorage.
     */
    class StorageInterface
    {
    public:

	StorageInterface () {}
	virtual ~StorageInterface () {}


	/**
	 * Query all attatched disks.
	 */
	virtual bool getDisks (list<string>& disks) = 0;


	/**
	 * Query partitions on all attatched disks.
	 */
	virtual bool getPartitions (list<PartitionInfo>& partitioninfos) = 0;

#if 0

	/**
	 * Query partitions on a single disks.
	 */
	virtual bool getPartitions (string disk, list<PartitionInfo>& partitioninfos) = 0;

#endif

	/**
	 * Quert capabilities of a filesystem type.
	 */
	virtual bool getFsCapabilities (FsType fstype, FsCapabilities& fscapabilities) = 0;

#if 0

	/**
	 * Create a new partition.
	 *
	 * @param disk name of disk, e.g. hda
	 * @param type type of partition to create, e.g. primary or extended
	 * @param size size of partition
	 * @param number gets assigned to the number of the new partition
	 */
	virtual bool createPartition (string disk, PartitionType type, long size,
				      int& number) = 0;

	/**
	 *
	 */
	virtual bool removePartition (string name) = 0;

	/**
	 *
	 */
	virtual bool resizePartition (string name, long size) = 0;

	/**
	 *  Destroys the partition table of a disk.
	 */
	virtual bool destroyPartitionTable (string disk) = 0;

	virtual bool createMd (...) = 0;
	virtual bool removeMd (...) = 0;

	virtual bool createLvmVg (...) = 0;
	virtual bool removeLvmVg (...) = 0;
	virtual bool extendLvmVg (...) = 0;
	virtual bool reduceLvmVg (...) = 0;

	virtual bool createLvmLv (...) = 0;
	virtual bool removeLvmLv (...) = 0;
	virtual bool resizeLvmLv (...) = 0;

	virtual bool createLoopFile (...) = 0;
	virtual bool removeLoopFile (...) = 0;

	virtual bool createEvmsContainer (...) = 0;
	virtual bool reomveEvmsContainer (...) = 0;
	virtual bool extendEvmsContainer (...) = 0;
	virtual bool reduceEvmsContainer (...) = 0;

	virtual bool createEvmsVolume (...) = 0;
	virtual bool removeEvmsVolume (...) = 0;
	virtual bool resizeEvmsVolume (...) = 0;

	virtual bool formatVolume (...) = 0;

	virtual bool changeMountPoint (...) = 0;

	virtual bool changeFstabOptions (...) = 0;

	/**
	 * Create a backup of the current state.
	 */
	virtual bool createBackupState (string name) = 0;

	/**
	 * Restore a backup of the current state.
	 */
	virtual bool restoreBackupState (string name) = 0;

	/**
	 * Delete a backup of the current state.
	 */
	virtual bool removeBackupState (string name) = 0;

	/**
	 * Commit the current state to the system.
	 */
	virtual bool commit () = 0;

#endif

    };


    StorageInterface* createStorageInterface (bool ronly = false,
					      bool testmode = false,
					      bool autodetect = true);


};


#endif
